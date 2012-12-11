#include <vector>
#include <assert.h>

#include "Transform.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;

Transform::Transform(Graph& graph) :
    _isValid(false),
    _graph(graph),
    _apply(),
    _src(),
    _dst()
{
}

bool Transform::isValid() const
{
    return _isValid;
}

void Transform::initTraversing()
{
    assert(_isValid);
    //Initialise la parcours en largeur
    _graph.initBFS();
    for (size_t i=0;i<_apply.size();i++) {
        //Met l'atome d'application comme parcouru
        size_t center = _apply[i].center();
        _graph.setState(center, true);
        //Ajoute comme sommet à parcourir les voisins de 
        //l'atome d'application différent des atomes excluts
        //(non encore ajoutés)
        for (size_t j=0;j<_graph.sizeEdge(center);j++) {
            size_t index = _graph.getEdge(center, j);
            if (
                _apply[i].exclude1() != index &&
                _apply[i].exclude2() != index &&
                _graph.getState(index) == false
            ) {
                _graph.addVertexToBFS(index);
            }
        }
    }
}

bool Transform::matchStar(const Star& src, const Star& dst, 
    std::vector<size_t>& matches) const
{
    assert(matches.empty());
    std::cout << "====Match Star===" << std::endl;
    size_t srcIndex = src.center();
    size_t dstIndex = dst.center();
    Atom* srcCenter = _graph.getVertex(srcIndex);
    Atom* dstCenter = _graph.getVertex(dstIndex);

    //Test en premier si le centre de l'étoile correspond
    if (srcCenter->isRepresent(dstCenter) == false) {
        std::cout << "No same center" << std::endl;
        return false;
    }

    size_t srcSize = _graph.sizeEdge(srcIndex);
    size_t dstSize = _graph.sizeEdge(dstIndex);
    std::cout << "srcSize " << srcSize << std::endl;
    std::cout << "dstSize " << dstSize << std::endl;

    //Liste des atomes voisins se src non exclus
    //Contient l'indice réel des atomes dans le graphe
    std::vector<size_t> srcEdges;
    //Liste des atomes voisins se dst non exclus
    //Contient l'indice réel des atomes dans le graphe
    std::vector<size_t> dstEdges;

    //Parcours les voisins de l'atome src et
    //Remplie srdEdges avec les non exclus
    for (size_t i=0;i<srcSize;i++) {
        size_t index = _graph.getEdge(srcIndex, i);
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
        size_t index = _graph.getEdge(dstIndex, i);
        if (
            dst.exclude1() != index &&
            dst.exclude2() != index
        ) {
            dstEdges.push_back(index);
        }
    }
    std::cout << "srcEdges " << srcEdges.size() << std::endl;
    std::cout << "dstEdges " << dstEdges.size() << std::endl;

    //Test si les voisins de dst sont au moins aussi
    //nombreux que les voisins de src (sinon, peut pas
    //être injectif)
    if (srcEdges.size() > dstEdges.size()) {
        std::cout << "Not injective" << std::endl;
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
    std::vector< std::vector<size_t> > srcLinks(srcEdges.size());
    std::vector< std::vector<size_t> > dstLinks(dstEdges.size());

    for (size_t i=0;i<srcEdges.size();i++) {
        for (size_t j=0;j<dstEdges.size();j++) {
            if (
                _graph.getVertex(srcEdges[i])
                ->isRepresent(
                    _graph.getVertex(dstEdges[j]))
            ) {
                srcLinks[i].push_back(j);
                dstLinks[j].push_back(i);
            }
        }
        //Test si tous les atomes voisins de src
        //ont au moins un atome voisin de dst
        //qui lui correspond
        if (srcLinks[i].size() == 0) {
            std::cout << "No represent" << std::endl;
            return false;
        }
    }
   
    //Contient pour les atomes src et dst l'atome de l'autre
    //coté au quel il est lié. -1 si pas de liaison
    std::vector<size_t> srcMatching(srcEdges.size(), -1);
    std::vector<size_t> dstMatching(dstEdges.size(), -1);

    //Initialise le couplage pour chaque atomes src si possible
    for (size_t i=0;i<srcEdges.size();i++) {
        for (size_t j=0;j<srcLinks[i].size();j++) {
            if (dstMatching[srcLinks[i][j]] != -1) {
                assert(srcMatching[i] == -1);
                srcMatching[i] = srcLinks[i][j];
                dstMatching[srcLinks[i][j]] = i;
                break;
            }
        }
    }

    //Défini une liste pour le parcours en largeur
    std::list<size_t> bfs;

    //Applique l'algorithme tant qu'un chemin améliorant
    //est trouvé
    bool changed = true;
    while (changed) {
        changed = false;
        //On recherche un sommets de src non saturé
        for (size_t i=0;i<srcEdges.size();i++) {
            if (srcMatching[i] == -1) {
                //On cherche par un parcours en largeur
                //du graphe un chemin alterné améliorant
                bfs.clear();
                bfs.push_back(i);
                size_t from = -1;
                bool even = true;
                while () {
                    size_t current = bfs.front();
                    bfs.pop_front();
                    if (!event && dstMatching[current] == -1) {
                        //
                    }
                    size_t size = even ? srcLinks[current].size() : dstLinks[current].size();
                    for (size_t j=0;j<size;j++) {
                        size_t index = even ? srcLinks[current][j] : dstLinks[current][j];
                        if (index != from) {
                            bfs.push_back(index);
                        }
                    }
                    from = current;
                }
                if () {
                    changed = true;
                    break;
                }
            }
        }
    }

    //
    for (size_t i=0;i<srcEdges.size();i++) {
        if (srcMatching[i] == -1) {
            std::cout << "No matching" << std::endl;
            return;
        }
    }

    //...

    //Les voisins de dst correspondants sont insérés dans 
    //matches
    for (size_t i=0;i<used.size();i++) {
        if (used[i]) {
            matches.push_back(dstEdges[i]);
        }
    }
    assert(matches.size() == srcEdges.size());

    return true;
}

bool Transform::replaceAtom(size_t src, size_t dst) const
{
    //Si les atomes sont les mêmes, on ne fait rien
    if (src == dst) {
        return true;
    }

    Atom* dstOldAtom = _graph.getVertex(dst);
    const Vector3& position = dstOldAtom->getPosition();
    Real radius = _graph.getVertex(src)->getRadius();

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
    Atom* dstNewAtom = _graph.getVertex(src)->create();
    dstOldAtom->transfertBonds(dstNewAtom);
    Global::getAtomManager()
        ->replace(dstOldAtom->getIndex(), dstNewAtom);
    _graph.replace(dst, dstNewAtom);
    dstNewAtom->setPosition(position);

    return true;
}

