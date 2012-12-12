#include "Bond.hpp"
#include "Atom.hpp"
#include "Global.hpp"
#include "Geometry.hpp"

using Ogre::Real;
using Ogre::Vector3;
using Ogre::ManualObject;
using Ogre::Math;

Bond::Bond(Atom* a1, Atom* a2, Ogre::Real length) :
    _end1(a1),
    _end2(a2),
    _length(length)
{
    assert(a1 != 0 && a2 != 0);
    assert(a1 != a2);
    //Création de l'apparence graphique de la liaison
    initNode();
}

Real Bond::getLength() const
{
    return _length;
}

Atom* Bond::getOtherEnd(const Atom* atom) const
{
    assert(atom != 0);
    return (_end1 == atom) ? _end2 : _end1;
}
        
void Bond::transfertEnd(Atom* src, Atom* dst)
{
    assert(src != 0);
    assert(dst != 0);
    if (_end1 == src) {
        _end1 = dst;
    } else {
        _end2 = dst;
    }
    updateNode();
}

void Bond::updateNode()
{
    Real distance = _end1->getPosition()
        .distance(_end2->getPosition())/2.0;
    Vector3 middle = 
        (_end1->getPosition()+_end2->getPosition())/2.0;
    _node->setPosition(middle);
    _node->setScale(Vector3(distance, 20, 20));
    _node->setOrientation(
        Vector3(1, 0, 0).getRotationTo(
            _end1->getPosition()-_end2->getPosition()
        )
    );
}

bool Bond::checkConstraint
    (const Atom* atom, const Vector3& position) const
{
    assert(atom != 0);
    assert(atom == _end1 || atom == _end2);

    Real distanceInit = _end1->getPosition()
        .distance(_end2->getPosition())/2.0;

    Real distance;
    if (atom == _end1) {
        distance = _end2->getPosition()
            .distance(position)/2.0;
    } else {
        distance = _end1->getPosition()
            .distance(position)/2.0;
    }

    if (distanceInit > _length) {
        //Si la contrainte n'était pas vérifiée avant
        //le déplacement, on accepte les déplacements
        //se reprochant de la contrainte
        return (distanceInit >= distance);
    } else {
        //Sinon, on n'accepte pas de déplacement
        //qui viole la contrainte
        return (distance <= _length);
    }
}
        
void Bond::remove()
{
    _end1->delBond(this);
    _end2->delBond(this);
    delete this;
}

void Bond::initNode()
{
    _manual = Geometry::cylinder(10);
    _node = Global::getSceneManager()
        ->getRootSceneNode()->createChildSceneNode();
    _node->attachObject(_manual);
    updateNode();
}

