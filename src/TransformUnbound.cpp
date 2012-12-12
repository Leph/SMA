#include <vector>
#include <assert.h>

#include "Transforms.hpp"
#include "Atoms.hpp"
#include "Global.hpp"

TransformUnbound::TransformUnbound(Graph* graph) :
    Transform(graph)
{
    assert(_graph->sizeVertex() > 0);
    assert(_graph->getVertex(0)->isType<Atom_Unbound>());

    //Construit la transformation
    //On cherche une étoiles associée avec une autre étoile
    buildTranformDoubleAssociation();
}

bool TransformUnbound::doTransformStep()
{
    assert(_isValid);

    //Parcours un sommet du graphe
    size_t index = _graph->nextVertexBFS();
    if (index == -1) {
        return false;
    }

    //Test pour tous les patterns src
    for (size_t i=0;i<_src.size();i++) {
        if (matchStar(_src[i], Star(index))) {
            //Recherche pour tous les voisins
            //une étoile qui correspond à l'autre étoile
            //dst
            size_t index2;
            bool success = false;
            for (size_t j=0;j<_graph->sizeEdge(index);j++) {
                index2 = _graph->getEdge(index, j);
                if (matchStar(_dst[i], Star(index2))) {
                    std::cout << "Unbound Matches" << std::endl;
                    //Destruction de la liaison entre les
                    //deux atomes matché
                    Atom* a1 = _graph->getVertex(index);
                    Atom* a2 = _graph->getVertex(index2);
                    Bond* bond;
                    if ((bond = a1->findBondTo(a2)) != 0) {
                        bond->remove();
                        std::cout << "->Unbounded" << std::endl;
                        std::cout << "->Unbounded" << std::endl;
                        std::cout << "->Unbounded" << std::endl;
                        std::cout << "->Unbounded" << std::endl;
                    }
                    success = true;
                    break;
                }
            }
            if (success) {
                break;
            }
        }
    }

    return true;
}

bool TransformUnbound::isActionAtom(const Atom* atom)
{
    assert(atom != 0);
    return atom->isType<Atom_Unbound>();
}

