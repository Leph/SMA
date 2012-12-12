#include <vector>
#include <assert.h>

#include "Transforms.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;

Transform::Transform(Graph* graph) :
    _isValid(false),
    _graph(graph),
    _apply(),
    _src(),
    _dst()
{
    assert(_graph != 0);
}

Transform::~Transform()
{
    delete _graph;
}

bool Transform::isValid() const
{
    return _isValid;
}
        
void Transform::buildTranformDoubleAssociation()
{
    //Parcours des voisins de l'atome d'action
    size_t sizeEdgeAction = _graph->sizeEdge(0);
    for (size_t i=0;i<sizeEdgeAction;i++) {
        size_t srcIndex = _graph->getEdge(0, i);
        //Si il s'agit d'un atome d'application
        //on l'enregistre
        if (_graph->getVertex(srcIndex)
            ->isType<Atom_Apply>()
        ) {
            _apply.push_back(Star(srcIndex, 0));
        }
        //Sinon on regarde si il peut s'agir d'une
        //étoile avec un atome d'association
        else {
            //Parcours des voisins de l'atome
            //On cherche les atomes d'association
            size_t sizeEdgeSrc = _graph
                ->sizeEdge(srcIndex);
            size_t associationFounded = 0;
            size_t associationIndex = 0;
            for (size_t j=0;j<sizeEdgeSrc;j++) {
                size_t index = _graph->getEdge(srcIndex, j);
                if (_graph->getVertex(index)
                    ->isType<Atom_Association>()
                ) {
                    associationFounded++;
                    associationIndex = index;
                }
            }
            //Si un unique atome d'association est trouvé
            //on vérifie qu'il ne lie que deux atomes
            if (associationFounded == 1) {
                if (_graph->sizeEdge(associationIndex) == 2) {
                    size_t dstIndex = 
                        _graph->getEdge(associationIndex, 0) == 
                        srcIndex ? 
                        _graph->getEdge(associationIndex, 1) : 
                        _graph->getEdge(associationIndex, 0);
                    _src.push_back(
                        Star(srcIndex, 0, associationIndex));
                    _dst.push_back(
                        Star(dstIndex, associationIndex));
                }
            }
        }
    }

    //Pour être valide, il faut que la transformation 
    //possède au moins un atome d'application voisin
    //de l'atome d'action
    //ainsi qu'un couple d'étoiles associés
    _isValid = _apply.size() > 0 && _src.size() > 0;
    assert(_src.size() == _dst.size());

    //Initialise le parcours du graphe
    if (_isValid) {
        initTraversing();
    }
}

void Transform::initTraversing()
{
    assert(_isValid);
    //Initialise la parcours en largeur
    _graph->initBFS();
    for (size_t i=0;i<_apply.size();i++) {
        //Met l'atome d'application comme parcouru
        size_t center = _apply[i].center();
        _graph->setState(center, true);
        //Ajoute comme sommet à parcourir les voisins de 
        //l'atome d'application différent des atomes excluts
        //(non encore ajoutés)
        for (size_t j=0;j<_graph->sizeEdge(center);j++) {
            size_t index = _graph->getEdge(center, j);
            if (
                _apply[i].exclude1() != index &&
                _apply[i].exclude2() != index &&
                _graph->getState(index) == false
            ) {
                _graph->addVertexToBFS(index);
            }
        }
    }
}

bool Transform::matchStar
    (const Star& src, const Star& dst) const
{
    size_t srcIndex = src.center();
    size_t dstIndex = dst.center();
    Atom* srcCenter = _graph->getVertex(srcIndex);
    Atom* dstCenter = _graph->getVertex(dstIndex);

    //Test en premier si le centre de l'étoile correspond
    if (srcCenter->isRepresent(dstCenter) == false) {
        return false;
    }

    size_t srcSize = _graph->sizeEdge(srcIndex);
    size_t dstSize = _graph->sizeEdge(dstIndex);

    //Liste des atomes voisins se src non exclus
    //Contient l'indice réel des atomes dans le graphe
    std::vector<size_t> srcEdges;
    //Liste des atomes voisins se dst non exclus
    //Contient l'indice réel des atomes dans le graphe
    std::vector<size_t> dstEdges;

    //Parcours les voisins de l'atome src et
    //Remplie srdEdges avec les non exclus
    for (size_t i=0;i<srcSize;i++) {
        size_t index = _graph->getEdge(srcIndex, i);
        if (
            src.exclude1() != index &&
            src.exclude2() != index
        ) {
            srcEdges.push_back(index);
        }
    }
    //Parcours les voisins de l'atome dst et
    //Remplie dstEdges avec les non exclus
    for (size_t i=0;i<dstSize;i++) {
        size_t index = _graph->getEdge(dstIndex, i);
        if (
            dst.exclude1() != index &&
            dst.exclude2() != index
        ) {
            dstEdges.push_back(index);
        }
    }

    //Test si les voisins de dst sont au moins aussi
    //nombreux que les voisins de src (sinon, peut pas
    //être injectif)
    if (srcEdges.size() > dstEdges.size()) {
        return false;
    }

    //Calcul le matching de deux graphes biparti en temps
    //polynomial. Utilise le concepte de couplage et de
    //chemins alternés augmentant

    //Construit le graphe biparti
    //srcLinks[i] correspond à srcEdges[i]
    //contient la liste des indices des atomes
    //correspondant à dstEdges[j]
    //dstLinks[i] correspond à dstEdges[i]
    //contient la liste des indices des atomes
    //correspondant à srcEdges[j]
    std::vector< std::vector<size_t> > 
        srcLinks(srcEdges.size());
    std::vector< std::vector<size_t> > 
        dstLinks(dstEdges.size());

    for (size_t i=0;i<srcEdges.size();i++) {
        for (size_t j=0;j<dstEdges.size();j++) {
            if (
                _graph->getVertex(srcEdges[i])
                ->isRepresent(
                    _graph->getVertex(dstEdges[j]))
            ) {
                srcLinks[i].push_back(j);
                dstLinks[j].push_back(i);
            }
        }
        //Test si tous les atomes voisins de src
        //ont au moins un atome voisin de dst
        //qui lui correspond
        if (srcLinks[i].size() == 0) {
            return false;
        }
    }
   
    //Contient pour les atomes src et dst l'atome de l'autre
    //coté au quel il est lié. -1 si pas de liaison
    std::vector<size_t> srcMatching(srcEdges.size(), -1);
    std::vector<size_t> dstMatching(dstEdges.size(), -1);

    //Initialise le couplage pour chaque atomes 
    //src si possible
    for (size_t i=0;i<srcEdges.size();i++) {
        for (size_t j=0;j<srcLinks[i].size();j++) {
            if (dstMatching[srcLinks[i][j]] != -1) {
                assert(srcMatching[i] == -1);
                srcMatching[i] = srcLinks[i][j];
                dstMatching[srcLinks[i][j]] = i;
                assert(dstMatching[srcMatching[i]] == i);
                break;
            }
        }
    }

    //Défini les structures de données pour le parcours 
    //en largeur et la construction de l'arbre alterné
    //Nodes contient les index des vertex dans srdEdges 
    //ou dstEdges
    //Parents contient l'index du sommet parent dans nodes
    //Sides vaut true si le sommet correpondant dans nodes 
    //et parents
    //appartient au coté src (sinon, dst)
    std::vector<size_t> nodes;
    std::vector<size_t> parents;
    std::vector<bool> sides;

    //Garde en mémoire les sommets ayant été parcourus
    std::vector<bool> srcStates;
    std::vector<bool> dstStates;

    //Applique l'algorithme tant qu'un chemin améliorant
    //est trouvé
    bool founded = true;
    while (founded) {
        founded = false;
        //On recherche un sommets de src non saturé
        for (size_t i=0;i<srcEdges.size();i++) {
            if (srcMatching[i] == -1) {
                //On cherche par un parcours en largeur
                //du graphe un chemin alterné améliorant
                nodes.clear();
                nodes.push_back(i);
                parents.clear();
                parents.push_back(-1);
                sides.clear();
                sides.push_back(true);
                srcStates.assign(srcEdges.size(), false);
                dstStates.assign(dstEdges.size(), false);
                srcStates[i] = true;
                size_t index = 0;
                while (true) {
                    assert(nodes.size() == parents.size());
                    assert(nodes.size() == sides.size());
                    //Si la liste est vide, on a tous parcouru
                    if (index >= nodes.size()) {
                        break;
                    }
                    assert(index < nodes.size());
                    size_t current = nodes[index];
                    //On test si on a trouvé un chemin
                    //augmentant
                    if (
                        !sides[index] && 
                        dstMatching[current] == -1
                    ) {
                        founded = true;
                        break;
                    }
                    //Sinon on continue le parcours en 
                    //ajoutant le successeur du sommet courant 
                    //(sans remonté dans l'arbre)
                    //si on est du coté src
                    if (sides[index]) {
                        size_t size = srcLinks[current].size();
                        for (size_t j=0;j<size;j++) {
                            size_t next = srcLinks[current][j];
                            if (dstStates[next] == false) {
                                nodes.push_back(next);
                                parents.push_back(index);
                                sides.push_back(false);
                                dstStates[next] = true;
                            }
                        }
                    } 
                    //Si on est du coté dst, on suit l'arrête
                    //qui est dans le couplage
                    else {
                        size_t next = dstMatching[current];
                        assert(next != -1);
                        assert(srcStates[next] == false);
                        nodes.push_back(next);
                        parents.push_back(index);
                        sides.push_back(true);
                        srcStates[next] = true;
                    }
                    index++;
                }
                //Si on a trouvé un chemin augmentant
                //on met à jours les couplages
                if (founded) {
                    while (index != -1) {
                        assert(sides[index] == false);
                        assert(parents[index] != -1);
                        dstMatching[nodes[index]] = 
                            nodes[parents[index]];
                        srcMatching[nodes[parents[index]]] = 
                            nodes[index];
                        assert(dstMatching[srcMatching[nodes[parents[index]]]] == nodes[parents[index]]);
                        assert(srcMatching[dstMatching[nodes[index]]] == nodes[index]);
                        index = parents[parents[index]];
                    }
                    break;
                }
            }
        }
    }

    //On test si tous les sommets src sont associés
    for (size_t i=0;i<srcMatching.size();i++) {
        if (srcMatching[i] == -1) {
            return false;
        } 
        assert(dstMatching[srcMatching[i]] == i);
    }

    return true;
}

bool Transform::replaceAtom(size_t src, size_t dst) const
{
    //Si les atomes sont les mêmes, on ne fait rien
    if (src == dst) {
        return true;
    }

    Atom* dstOldAtom = _graph->getVertex(dst);
    const Vector3& position = dstOldAtom->getPosition();
    Real radius = _graph->getVertex(src)->getRadius();

    //Test si il y a la place de remplacer l'atome
    //dst par un atome src peut être plus gros
    if (
        Global::getPositionResolver()
            ->checkCollisionAtoms
            (position, radius, dstOldAtom) ||
        Global::getTerrain()
            ->checkCollision(position, radius)
    ) {
        return false;
    }

    //Place le nouvel atome et supprime l'ancien
    //dans l'atome manager ainsi que
    //dans le graph
    Atom* dstNewAtom = _graph->getVertex(src)->create();
    dstOldAtom->transfertBonds(dstNewAtom);
    Global::getAtomManager()
        ->replace(dstOldAtom->getIndex(), dstNewAtom);
    _graph->replace(dst, dstNewAtom);
    dstNewAtom->setPosition(position);

    return true;
}

