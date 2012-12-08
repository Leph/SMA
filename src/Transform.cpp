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
    //Initialise la parcours en largeur
    _graph.initBFS();
    for (size_t i=0;i<_apply.size();i++) {
        //Met l'atome d'application comme parcouru
        size_t center = _apply[i].center();
        _graph.setState(center, true);
        //Ajoute comme sommet à parcourir les voisins de 
        //l'atome d'application différent des atomes excluts
        for (size_t j=0;j<_graph.sizeEdge(center);j++) {
            size_t index = _graph.getEdge(center, j);
            if (
                _apply[i].exclude1() != index &&
                _apply[i].exclude2() != index
            ) {
                _graph.addVertexToBFS(index);
            }
        }
    }
}

bool Transform::matchStar
    (const Star& src, const Star& dst) const
{
    size_t srcIndex = src.center();
    size_t dstIndex = dst.center();
    Atom* srcCenter = _graph.getVertex(srcIndex);
    Atom* dstCenter = _graph.getVertex(dstIndex);

    //Déjà, test si le centre de l'étoile correspond
    if (srcCenter->isRepresent(dstCenter) == false) {
        return false;
    }

    size_t srcSizeEdge = _graph.sizeEdge(srcIndex);
    size_t dstSizeEdge = _graph.sizeEdge(dstIndex);

    std::vector< std::vector<size_t> > links;
    std::vector<size_t> results;
    
    for (size_t i=0;i<srcSizeEdge;i++) {
        size_t index1 = _graph.getEdge(srcIndex, i);
        if (
            src.exclude1() != index1 && 
            src.exclude2() != index1
        ) {
            links.push_back(std::vector<size_t>());
            for (size_t j=0;j<dstSizeEdge;j++) {
                size_t index2 = _graph.getEdge(dstIndex, j);
                if (
                    dst.exclude1() != index2 && 
                    dst.exclude2() != index2 &&
                    _graph.getVertex(index1)
                        ->isRepresent(_graph.getVertex(index2))
                ) {
                    links[links.size()-1].push_back(index2);
                }
            }
            results.push_back(links[links.size()-1][0]);
        }
    }

    while () {
        for (size_t i=0;links.size();i++) {

        }
    }

    return true;
}

