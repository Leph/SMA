#include <assert.h>

#include "Graph.hpp"
#include "Global.hpp"

using Ogre::Vector3;
using Ogre::ManualObject;

Graph::Graph() :
    _vertices(),
    _states(),
    _edges(),
    _bfs(),
    _node(0)
{
}

Graph::~Graph()
{
    if (_node != 0) {
        _node->removeAllChildren();
        Global::getSceneManager()->destroySceneNode(_node);
    }
}

void Graph::build(Atom* atom)
{
    assert(atom != 0);

    //Réinitialisation des structures de
    //données
    clear();
      
    //Récupération du voisinage de l'atome
    std::list<Atom*>& neighbors = 
        Global::getPositionResolver()->findAtoms(
            atom->getPosition(), 
            Graph::DISTANCE_NEIGHBOURHOOD, 
            atom
        );

    //Ajout de tous les atomes au graphe
    //en commençant par l'atome au centre (index 0)
    addVertex(atom);
    std::list<Atom*>::iterator it = neighbors.begin();
    while (it != neighbors.end()) {
        addVertex(*it);
        it++;
    }

    //Parcours des sommets et ajout des arrêtes
    for (size_t i=0;i<_vertices.size();i++) {
        for (size_t j=i+1;j<_vertices.size();j++) {
            if (
                _vertices[i]->getPosition()
                .squaredDistance(_vertices[j]->getPosition()) 
                <= Graph::DISTANCE_EDGE*Graph::DISTANCE_EDGE 
                || _vertices[i]->isBoundTo(_vertices[j])
            ) {
                addEdge(i, j);
            }
        }
    }

    //Créer la représentation graphique
    initNode();

    //Initialise la parcours
    initBFS();
}

void Graph::clear()
{
    //Supprime la représentation graphique
    if (_node != 0) {
        _node->removeAllChildren();
        Global::getSceneManager()->destroySceneNode(_node);
        _node = 0;
    }

    //Supprime les données
    _vertices.clear();
    _states.clear();
    _edges.clear();
}
        
size_t Graph::sizeVertex() const
{
    return _vertices.size();
}
        
Atom* Graph::getVertex(size_t index) const
{
    assert(index >=0 && index < _vertices.size());

    return _vertices[index];
}
        
size_t Graph::sizeEdge(size_t index) const
{
    assert(index >=0 && index < _edges.size());

    return _edges[index].size();
}
        
size_t Graph::getEdge(size_t index, size_t i) const
{
    assert(index >=0 && index < _edges.size());
    assert(i >=0 && i < _edges[index].size());

    return _edges[index][i];
}

void Graph::initBFS()
{
    assert(_vertices.size() == _states.size());
    for (size_t i=0;i<_states.size();i++) {
        _states[i] = false;
    }
    _bfs.clear();
}
        
void Graph::setState(size_t index, bool value)
{
    assert(index >= 0 && index < _states.size());
    _states[index] = value;
}

void Graph::addVertexToBFS(size_t index)
{
    assert(index >= 0 && index < _vertices.size());
    assert(_states[index] == false);
    _bfs.push_back(index);
    _states[index] = true;
}
        
size_t Graph::nextVertexBFS()
{
    if (_bfs.empty()) {
        return -1;
    }

    size_t index = _bfs.front();
    _bfs.pop_front();

    for (size_t i=0;i<_edges[index].size();i++) {
        size_t j = _edges[index][i];
        if (_states[j] == false) {
            _states[j] = true;
            _bfs.push_back(j);
        }
    }

    return index;
}

size_t Graph::addVertex(Atom* atom)
{
    assert(atom != 0);
    //Vérifie que l'atome n'est pas déjà présent 
    //dans le graphe
    for (size_t i=0;i<_vertices.size();i++) {
        assert(_vertices[i] != atom);
    }
    
    _vertices.push_back(atom);
    _states.push_back(false);
    _edges.push_back(std::vector<size_t>());

    return _vertices.size()-1;
}
        
void Graph::addEdge(size_t index1, size_t index2)
{
    assert(index1 >= 0 && index2 >= 0);
    assert(
        index1 < _edges.size() && 
        index2 < _edges.size()
    );
    //Vérifie que l'arrête n'est pas déjà présente
    //dans le graphe
    for (size_t i=0;i<_edges[index1].size();i++) {
        assert(_edges[index1][i] != index2);
    }
    for (size_t i=0;i<_edges[index2].size();i++) {
        assert(_edges[index2][i] != index1);
    }

    _edges[index1].push_back(index2);
    _edges[index2].push_back(index1);
}

void Graph::initNode()
{
    assert(_node == 0);

    ManualObject* manual = Global::getSceneManager()
        ->createManualObject();
    manual->begin(
        "BaseWhiteNoLighting", 
        Ogre::RenderOperation::OT_LINE_LIST
    );
    for (size_t i=0;i<_edges.size();i++) {
        for (size_t j=0;j<_edges[i].size();j++) {
            manual->position(
                _vertices[i]->getPosition());
            manual->position(
                _vertices[_edges[i][j]]->getPosition());

            manual->position(
                _vertices[i]->getPosition()+Vector3(0, 10, 0));
            manual->position(
                _vertices[_edges[i][j]]->getPosition()+Vector3(0, 10, 0));
            manual->position(
                _vertices[i]->getPosition()+Vector3(10, 0, 0));
            manual->position(
                _vertices[_edges[i][j]]->getPosition()+Vector3(10, 0, 0));
            manual->position(
                _vertices[i]->getPosition()+Vector3(0, 0, 10));
            manual->position(
                _vertices[_edges[i][j]]->getPosition()+Vector3(0, 0, 10));
            
            manual->position(
                _vertices[i]->getPosition()+Vector3(0, -10, 0));
            manual->position(
                _vertices[_edges[i][j]]->getPosition()+Vector3(0, -10, 0));
            manual->position(
                _vertices[i]->getPosition()+Vector3(-10, 0, 0));
            manual->position(
                _vertices[_edges[i][j]]->getPosition()+Vector3(-10, 0, 0));
            manual->position(
                _vertices[i]->getPosition()+Vector3(0, 0, -10));
            manual->position(
                _vertices[_edges[i][j]]->getPosition()+Vector3(0, 0, -10));
        }
    }
    manual->end();

    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(manual);
}

