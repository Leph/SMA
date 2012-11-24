#include <assert.h>

#include "Graph.hpp"

Graph::Graph() :
    _vertices(),
    _edges()
{
}

size_t Graph::addVertex(Atom* atom)
{
    assert(atom != 0);
    for (size_t i=0;i<_vertices.size();i++) {
        assert(_vertices[i] != atom);
    }
    
    _vertices.push_back(atom);
    _edges.push_back(std::vector());

    return _vertices.size()-1;
}
        
void Graph::addEdge(size_t index1, size_t index2)
{
    assert(index1 >= 0 && index2 >= 0);
    assert(
        index1 < _edges.size() && 
        index2 < _edges.size()
    );
    for (size_t i=0;i<_edges[index1].size();i++) {
        assert(_edges[index1][i] != index2);
    }
    for (size_t i=0;i<_edges[index2].size();i++) {
        assert(_edges[index2][i] != index1);
    }

    _edges[index1].push_back(index2);
    _edges[index2].push_back(index1);
}

void Graph::clear()
{
    _vertices.clear();
    _edges.clear();
}

