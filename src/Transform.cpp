#include <vector>
#include <assert.h>

#include "Transform.hpp"

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

bool Transform::matchStar
    (const Star& src, const Star& dst) const
{
    std::cout << "====Match Star===" << std::endl;
    size_t srcIndex = src.center();
    size_t dstIndex = dst.center();
    Atom* srcCenter = _graph.getVertex(srcIndex);
    Atom* dstCenter = _graph.getVertex(dstIndex);

    //Test en premier si le centre de l'étoile correspond
    if (srcCenter->isRepresent(dstCenter) == false) {
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
    //valeur : ...0000-1 pour que la première valeur après 
    //incrémentation soit ...0000
    for (size_t i=0;i<links.size();i++) {
        associations.push_back(0);
    }
    associations[0] = -1;
    assert(associations.size() == srcEdges.size());

    //Initialise les états de used à non
    //utilisé
    for (size_t i=0;i<dstEdges.size();i++) {
        used.push_back(false);
    }
    assert(used.size() == dstEdges.size());

    while(true) {
        //Reset les valeurs de used
        for (size_t i=0;i<used.size();i++) {
            used[i] = false;
        }
        //Incrémente de "un" le vecteur
        //des associations (itération sur
        //toutes les valeurs possibles)
        size_t digit = 0;
        bool matched = true;
        while (true) {
            std::cout << ">>> loop " << digit << " (" << links[digit].size() << ") " << matched << std::endl;
            bool carry = false;
            //On incrémente le digit
            associations[digit]++;
            //Si on dépasse les valeurs possible
            //on retourne à 0 et on continue avec le 
            //prochain digit
            if (associations[digit] == links[digit].size()) {
                associations[digit] = 0;
                carry = true;
                std::cout << "carry true" << std::endl;
            }
            //Sinon, on sort de la boucle
            else {
                carry = false;
                std::cout << "carry false" << std::endl;
            }
            //On test que la valeur n'est pas déjà prise
            if (used[links[digit][associations[digit]]] == true) {
                //Si c'est le cas, la configuration n'est pas valide
                matched = false;
                std::cout << "unvalid" << std::endl;
            } else {
                //Mise à jour des atomes voisins de dst utilisé
                used[links[digit][associations[digit]]] = true;
                std::cout << "valid" << std::endl;
            }
            //On sort de la boucle si il n'y a pas de retenu,
            //le vecteur est incrémenté
            if (!carry) {
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
        //Si on est sortie de la boucle avec le flag
        //match = true, un résultat est trouvé
        if (matched) {
            break;
        }
        //Sinon, on continue à explorer
        //toutes les valeurs
    }

    return true;
}

