#include "Terrain.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::ManualObject;

Terrain::Terrain() :
    _size(2000),
    _subdivision(10),
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
    ManualObject* manual = Global::getSceneManager()
        ->createManualObject();

    manual->begin(
        "BaseWhiteNoLighting", 
        Ogre::RenderOperation::OT_LINE_LIST
    );
    for (long i=0;i<=_subdivision;i++) {
        manual->position(-1,  1,  i*1/_subdivision);
        manual->position(-1, -1,  i*1/_subdivision);
        manual->position(-1,  1, -i*1/_subdivision);
        manual->position(-1, -1, -i*1/_subdivision);
        
        manual->position( 1,  1,  i*1/_subdivision);
        manual->position( 1, -1,  i*1/_subdivision);
        manual->position( 1,  1, -i*1/_subdivision);
        manual->position( 1, -1, -i*1/_subdivision);
        
        manual->position( 1, -1,  i*1/_subdivision);
        manual->position(-1, -1,  i*1/_subdivision);
        manual->position( 1, -1, -i*1/_subdivision);
        manual->position(-1, -1, -i*1/_subdivision);
        
        manual->position( 1,  1,  i*1/_subdivision);
        manual->position(-1,  1,  i*1/_subdivision);
        manual->position( 1,  1, -i*1/_subdivision);
        manual->position(-1,  1, -i*1/_subdivision);

        manual->position(-i*1/_subdivision,  1, -1);
        manual->position(-i*1/_subdivision, -1, -1);
        manual->position( i*1/_subdivision,  1, -1);
        manual->position( i*1/_subdivision, -1, -1);
        
        manual->position(-i*1/_subdivision,  1,  1);
        manual->position(-i*1/_subdivision, -1,  1);
        manual->position( i*1/_subdivision,  1,  1);
        manual->position( i*1/_subdivision, -1,  1);

        manual->position(-i*1/_subdivision,  1,  1);
        manual->position(-i*1/_subdivision,  1, -1);
        manual->position( i*1/_subdivision,  1,  1);
        manual->position( i*1/_subdivision,  1, -1);

        manual->position(-i*1/_subdivision, -1,  1);
        manual->position(-i*1/_subdivision, -1, -1);
        manual->position( i*1/_subdivision, -1,  1);
        manual->position( i*1/_subdivision, -1, -1);

        manual->position( 1, -i*1/_subdivision, -1);
        manual->position(-1, -i*1/_subdivision, -1);
        manual->position( 1,  i*1/_subdivision, -1);
        manual->position(-1,  i*1/_subdivision, -1);

        manual->position( 1, -i*1/_subdivision,  1);
        manual->position(-1, -i*1/_subdivision,  1);
        manual->position( 1,  i*1/_subdivision,  1);
        manual->position(-1,  i*1/_subdivision,  1);

        manual->position( 1, -i*1/_subdivision,  1);
        manual->position( 1, -i*1/_subdivision, -1);
        manual->position( 1,  i*1/_subdivision,  1);
        manual->position( 1,  i*1/_subdivision, -1);

        manual->position(-1, -i*1/_subdivision,  1);
        manual->position(-1, -i*1/_subdivision, -1);
        manual->position(-1,  i*1/_subdivision,  1);
        manual->position(-1,  i*1/_subdivision, -1);
    }
    manual->end();

    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(manual);
    _node->setPosition(Vector3(0, 0, 0));
    _node->setScale(Vector3(_size, _size, _size));
}

