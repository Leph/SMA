#include <vector>
#include <assert.h>

#include "TransformBound.hpp"
#include "Atoms.hpp"

TransformBound::TransformBound(Graph& graph) :
    Transform(graph)
{
    assert(_graph.sizeVertex() > 0);
    assert(_graph.getVertex(0)->isType<Atom_Bound>());

    //Construit la transformation
    //On cherche une étoiles associée avec une autre étoile
    buildTranformDoubleAssociation();
}

bool TransformBound::doTransformStep()
{
    assert(_isValid);

    //Parcours un sommet du graphe
    size_t index = _graph.nextVertexBFS();
    if (index == -1) {
        return false;
    }

    //TODO

    return true;
}

