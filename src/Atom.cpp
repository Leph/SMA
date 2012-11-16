#include <assert.h>

#include "Atom.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::Entity;
using Ogre::Any;

Atom::Atom(Real radius, Vector3 position) :
    _radius(radius),
    _position(position),
    _force(Vector3(0, 0, 0)),
    _node(0)
{
    initNode();
}

Atom::~Atom()
{
    _node->removeAllChildren();
    Global::getSceneManager()->destroySceneNode(_node);
}

Real Atom::getRadius() const
{
    return _radius;
}

const Vector3& Atom::getPosition() const
{
    return _position;
}

void Atom::move(Real dt)
{
    assert(dt > 0);
    _position += _force*dt;
    _node->setPosition(_position);
}

void Atom::computeMove()
{
    _force = Vector3(0, 0, 0);
    _force += applyGravity();
    _force += applyBrownian();
}

void Atom::initNode()
{
    //Creer une sphere de rayon _radius pour la 
    //représentation graphique de l'atome
    //La sphère par default de Ogre à un rayon
    //de 50 unités
    Entity* sphere = Global::getSceneManager()
        ->createEntity(Ogre::SceneManager::PT_SPHERE);
    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(sphere);
    _node->setScale(
        Vector3(_radius/50, _radius/50, _radius/50));
    _node->setPosition(_position);
    _node->showBoundingBox(true);

    //Attache à l'entité un pointeur vers cette instance afin
    //de pouvoir récupérer l'objet Atom à partir du noeud
    //de scene
    sphere->getUserObjectBindings().setUserAny(
        Any(this));
}

Vector3 Atom::applyGravity()
{
    return Vector3(0, 0, -2.0);
}

Vector3 Atom::applyBrownian()
{
    return Vector3(0, 0, 0);
}

