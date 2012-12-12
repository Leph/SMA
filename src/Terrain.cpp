#include "Terrain.hpp"
#include "Geometry.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::ManualObject;

Terrain::Terrain() :
    _size(2000),
    _subdivision(5),
    _node(0)
{
    //Création de l'apparence graphique de l'atome
    initNode();
}

Terrain::~Terrain()
{
    _node->removeAllChildren();
    Global::getSceneManager()->destroySceneNode(_node);
}

bool Terrain::checkCollision
    (const Vector3& position, Real radius) const
{
    return 
        position.x-radius<-_size || position.x+radius>_size ||
        position.y-radius<-_size || position.y+radius>_size ||
        position.z-radius<-_size || position.z+radius>_size;
}

void Terrain::initNode()
{
    ManualObject* manual = Geometry::terrain(_subdivision);
    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(manual);
    _node->setPosition(Vector3(0, 0, 0));
    _node->setScale(Vector3(_size, _size, _size));
}

