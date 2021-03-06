#include <sstream>
#include <assert.h>

#include "Atom.hpp"
#include "Global.hpp"
#include "Geometry.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::Entity;
using Ogre::ManualObject;
using Ogre::Any;
using Ogre::Math;
using Ogre::String;
using Ogre::ColourValue;

Atom::Atom(Real radius, const Vector3& position) :
    _radius(radius),
    _position(position),
    _brownianMotion(),
    _brownianCounter(),
    _bonds(),
    _isFixed(false),
    _index(-1)
{
    //initialisation du mouvement brownien
    _brownianMotion = Vector3(
        Math::RangeRandom(-1, 1),
        Math::RangeRandom(-1, 1),
        Math::RangeRandom(-1, 1)
    ).normalise();
    _brownianCounter = 0;
}

Atom::~Atom()
{
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

void Atom::setPosition(const Ogre::Vector3& position)
{
    //Mise à jour de la position et du noeud Ogre
    _position = position;
    _node->setPosition(_position);
    
    //Mise à jour des liaisons de l'atome
    for (size_t i=0;i<_bonds.size();i++) {
        _bonds[i]->updateNode();
    }

    //Mise à jour des structures Ogre de la scene (octree)
    Global::getSceneManager()->_updateSceneGraph(0);
}

void Atom::move(Real dt)
{
    assert(dt > 0);

    //Ne fait rien si l'atome est fixe
    if (_isFixed) {
        return;
    }

    //Calcul des forces appliquées sur l'atome
    Vector3 force = Vector3(0, 0, 0);
    force += applyGravity();
    force += applyBrownian(dt);

    //Intégration de la position
    Vector3 motion = force*dt;
    //Vérification des collisions et autres contraintes
    //spatial
    setPosition(Global::getPositionResolver()
        ->resolve(this, motion));
}
        
void Atom::addBond(Bond* bond)
{
    assert(bond != 0);
    assert(!isBoundTo(bond->getOtherEnd(this)));

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

bool Atom::isBoundTo(const Atom* atom) const
{
    assert(atom != 0);

    return findBondTo(atom) != 0;
}

Bond* Atom::findBondTo(const Atom* atom) const
{
    assert(atom != 0);
    
    for(size_t i=0;i<_bonds.size();i++) {
        if (_bonds[i]->getOtherEnd(this) == atom) {
            return _bonds[i];
        }
    }

    return 0;
}
        
void Atom::transfertBonds(Atom* atom)
{
    assert(atom != 0);
    for (size_t i=0;i<_bonds.size();i++) {
        //Vérifie que l'on est mas lié à l'atome
        if (_bonds[i]->getOtherEnd(this) == atom) {
            atom->delBond(_bonds[i]);
            delete _bonds[i];
        } 
        //Vérifie que la liaison n'existe pas déjà
        else if (atom->isBoundTo(
            _bonds[i]->getOtherEnd(this))
        ) {
            _bonds[i]->getOtherEnd(this)->delBond(_bonds[i]);
            delete _bonds[i];
        }else {
            _bonds[i]->transfertEnd(this, atom);
            atom->addBond(_bonds[i]);
        }
    }
    _bonds.clear();
}

size_t Atom::getIndex() const
{
    assert(_index != -1);

    return _index;
}
        
void Atom::setIndex(size_t index)
{
    _index = index;
}
        
bool Atom::isFixed() const
{
    return _isFixed;
}
        
void Atom::setFixed(bool fixed)
{
    _isFixed = fixed;
}

void Atom::initNode
    (ManualObject* manual, const ColourValue& colour)
{
    _manual = manual;

    //Détruit le noeud de scene si
    //déjà définie
    if (_node != 0) {
        _node->removeAllChildren();
        Global::getSceneManager()->destroySceneNode(_node);
    }

    /**
     * Création du noeud de scene Ogre
     * et mise à jour de sa position et taille
     */
    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(_manual);
    _node->setScale(
        Vector3(_radius, _radius, _radius));
    _node->setPosition(_position);
    _node->showBoundingBox(false);

    //Attache à l'entité un pointeur vers cette instance afin
    //de pouvoir récupérer l'objet Atom à partir du noeud
    //de scene
    _manual->getUserObjectBindings().setUserAny(
        Any(this));

    //Conversion de la couleur en nom de 
    //materiel
    std::ostringstream oss;
    oss << colour.getAsRGBA();
    String materialName = oss.str();

    //Création d'un nouveau matériel à partir du matériel
    //de base et mise à jour de la couleur
    Ogre::MaterialPtr material = _manual->getSection(0)
        ->getMaterial().getPointer()->clone(materialName);
    material.getPointer()->setDiffuse(colour);
    _manual->getSection(0)->setMaterialName(materialName);
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
    return 20*_brownianMotion;
}

