#include <assert.h>

#include "Graph.hpp"
#include "Global.hpp"

using Ogre::ManualObject;

Graph::Graph() :
    _vertices(),
    _edges(),
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
    _edges.clear();
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
            manual->position(_vertices[i]->getPosition());
            manual->position(_vertices[_edges[i][j]]->getPosition());
        }
    }
    manual->end();

    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(manual);
}

