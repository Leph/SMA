#include <assert.h>

#include "Atom.hpp"
#include "Global.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::Entity;
using Ogre::Any;
using Ogre::Math;

Atom::Atom(Real radius, const Vector3& position) :
    _radius(radius),
    _position(position),
    _brownianMotion(),
    _brownianCounter(),
    _node(0),
    _bonds()
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
    //Détruit le noeud de scene
    _node->removeAllChildren();
    Global::getSceneManager()->destroySceneNode(_node);

    //Détruit les liaisons associées
    while (!_bonds.empty()) {
        _bonds[0]->remove();
    }
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
    Vector3 motion = force*dt;
    //Vérification des collisions et autres contraintes
    //spatial
    _position = Global::getPositionResolver()
        ->resolve(this, motion);
    _node->setPosition(_position);

    //Mise à jour des liaisons de l'atome
    for (size_t i=0;i<_bonds.size();i++) {
        _bonds[i]->updateNode();
    }

    //Mise à jour des structures Ogre de la scene (octree)
    Global::getSceneManager()->_updateSceneGraph(0);
}
        
void Atom::addBond(Bond* bond)
{
    assert(bond != 0);
    _bonds.push_back(bond);
}
        
void Atom::delBond(Bond* bond)
{
    assert(bond != 0);
    size_t i=0;
    while (i < _bonds.size() && _bonds[i] != bond) {
        i++;
    }
    assert(i < _bonds.size());

    _bonds[i] = _bonds[_bonds.size()-1];
    _bonds.pop_back();
}
        
bool Atom::checkConstraintBonds
    (const Vector3& position) const
{
    for (size_t i=0;i<_bonds.size();i++) {
        if (!_bonds[i]->checkConstraint(this, position)) {
            return false;
        }
    }

    return true;
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
    _node->showBoundingBox(false);

    //Attache à l'entité un pointeur vers cette instance afin
    //de pouvoir récupérer l'objet Atom à partir du noeud
    //de scene
    sphere->getUserObjectBindings().setUserAny(
        Any(this));
}

Vector3 Atom::applyGravity()
{
    return Vector3(0, -4.0, 0);
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

