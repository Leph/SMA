#include <assert.h>

#include "Atom.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::Entity;

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
    //Creer une sphere de rayon _radius pour la représentation 
    //graphique de l'atome
    Entity* sphere = Global::getSceneManager()
        ->createEntity(Ogre::SceneManager::PT_SPHERE);
    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(sphere);
    _node->setScale(Vector3(_radius, _radius, _radius));
    _node->setPosition(_position);
}

Vector3 Atom::applyGravity()
{
    return Vector3(0, 0, -2.0);
}

Vector3 Atom::applyBrownian()
{
    return Vector3(0, 0, 0);
}

