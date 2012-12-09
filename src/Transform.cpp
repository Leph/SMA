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

    //Liste les liens possibles des atomes voisins
    //de src avec les atomes voisins de dst
    //links[i] correspond au i-ème atome dans srcEdge[i]
    //Les indices des atomes voisins de dst dans links[i] j
    //correspondent aux atomes j-ième atome dans dstEdge[j]
    std::vector< std::vector<size_t> > links;

    //Parcours les voisins de src et dst pour 
    //remplir links
    for (size_t i=0;i<srcEdges.size();i++) {
        links.push_back(std::vector<size_t>());
        for (size_t j=0;j<dstEdges.size();j++) {
            if (
                _graph.getVertex(srcEdges[i])
                ->isRepresent(
                    _graph.getVertex(dstEdges[j]))
            ) {
                links[links.size()-1].push_back(j);
            }
        }
        //Test si tous les atomes voisins de src
        //ont au moins un atome voisin de dst
        //qui lui correspond
        if (links[links.size()-1].size() == 0) {
            std::cout << "No represent" << std::endl;
            return false;
        }
    }
    assert(links.size() == srcEdges.size());
    
    //Contient pour chaque atomes voisins de src l'indice
    //du voisin de dst auquel il est lié
    //association[i]=j correspond à srdEdges[i] et j
    //correspond ) dstEdges[links[i][j]]
    std::vector<size_t> associations;

    //Contient pour chaque atomes voisins de dst non
    //exclut un booleen indiquant si l'atomes est utilisé (lié)
    //dans le tableau d'association
    //used[i] correspond à dstEdges[i]
    std::vector<bool> used;

    //Initialise associations avec les premières
    //valeurs possibles dans links pour tous les atomes
    for (size_t i=0;i<links.size();i++) {
        associations.push_back(0);
    }
    assert(associations.size() == srcEdges.size());

    //Initialise les états de used à non
    //utilisé
    for (size_t i=0;i<dstEdges.size();i++) {
        used.push_back(false);
    }
    assert(used.size() == dstEdges.size());

    while(true) {
        std::cout << ">>> loop " << std::endl;
        //Reset les valeurs de used
        for (size_t i=0;i<used.size();i++) {
            used[i] = false;
        }
        //Test si la configuration est valide
        bool matched = true;
        for (size_t i=0;i<associations.size();i++) {
            //On regarde si un voisins de dst est utilisé 
            //deux fois
            if (used[links[i][associations[i]]] == true) {
                //La configuration est invalide, on sort de la
                //boucle
                matched = false;
                break;
            } else {
                //La configuration est valide pour le moment
                used[links[i][associations[i]]] = true;
            }
        }
        //Si la configuration est valide, on sort de la boucle
        //d'exploration
        //Sinon on incrémente
        if (matched) {
            std::cout << "Valid !" << std::endl;
            break;
        }
        //Incrémente de "un" le vecteur
        //des associations (itération sur
        //toutes les valeurs possibles)
        size_t digit = 0;
        while (true) {
            std::cout << "   loop digit " << digit << "(" << links[digit].size() << ")" << std::endl;
            //On incrémente le digit
            associations[digit]++;
            //Si on dépasse les valeurs possible
            //on retourne à 0 et on continue avec le 
            //prochain digit
            if (associations[digit] == links[digit].size()) {
                associations[digit] = 0;
                std::cout << "carry true" << std::endl;
            }
            //Sinon, on sort de la boucle, le vecteur est
            //incrémenté
            else {
                std::cout << "carry false" << std::endl;
                break;
            }
            digit++;
            //Si on a parcourus tous le vecteur
            //association, celà veut dire que l'ont a testé
            //toutes les valeurs sans résultat
            if (digit == associations.size()) {
                std::cout << "Overflow, break" << std::endl;
                return false;
            }
        }
    }

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
    dstNewAtom->setPosition(position);

    return true;
}

