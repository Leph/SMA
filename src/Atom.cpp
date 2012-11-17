#include <assert.h>

#include "Atom.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::Entity;
using Ogre::Any;
using Ogre::Math;

Atom::Atom(Real radius, Vector3 position) :
    _radius(radius),
    _position(position),
    _brownianMotion(),
    _brownianCounter(),
    _node(0)
{
    //initialisation du mouvement brownien
    _brownianMotion = Vector3(
        Math::RangeRandom(-1, 1),
        Math::RangeRandom(-1, 1),
        Math::RangeRandom(-1, 1)
    ).normalise();
    _brownianCounter = 0;

    //Création de l'apparence graphique de l'atome
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

    //Calcul des forces appliquées sur l'atome
    Vector3 force = Vector3(0, 0, 0);
    force += applyGravity();
    force += applyBrownian(dt);

    //Intégration de la position
    _position += force*dt;
    _node->setPosition(_position);
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

Vector3 Atom::applyBrownian(Real dt)
{
    _brownianCounter -= dt;
    if (_brownianCounter <= 0) {
        _brownianMotion += Vector3(
            Math::RangeRandom(-1.0, 1.0),
            Math::RangeRandom(-1.0, 1.0),
            Math::RangeRandom(-1.0, 1.0)
        );
        _brownianMotion.normalise();
        _brownianCounter = Math::RangeRandom(0.0, 10);
    }
    return 10*_brownianMotion;
}

