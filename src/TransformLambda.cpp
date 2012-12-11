#include <vector>
#include <assert.h>

#include "TransformLambda.hpp"
#include "Atoms.hpp"

TransformLambda::TransformLambda(Graph* graph) :
    Transform(graph)
{
    assert(_graph->sizeVertex() > 0);
    assert(_graph->getVertex(0)->isType<Atom_Lambda>());

    //Construit la transformation
    //On cherche une étoiles associée avec une autre étoile
    buildTranformDoubleAssociation();
}

bool TransformLambda::doTransformStep()
{
    assert(_isValid);

    //Parcours un sommet du graphe
    size_t index = _graph->nextVertexBFS();
    if (index == -1) {
        return false;
    }

    //Test pour tous les patterns src
    std::vector<size_t> matches;
    for (size_t i=0;i<_src.size();i++) {
        matches.clear();
        //Test du pattern d'étoile
        if (matchStar(_src[i], Star(index), matches)) {
            std::cout << "Matches" << std::endl;
            //Remplace le centre de l'étoile ayant matché
            //avec le centre de l'étoile dst
            bool success = 
                replaceAtom(_dst[i].center(), index);
            //Le remplacement à réussi
            if (success) {
                std::cout << "->Replaced" << std::endl;
                break;
            }
        } 
    }

    return true;
}

