#include <assert.h>

#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::Real;
using Ogre::ColourValue;

Atom_Term_Virt::Atom_Term_Virt(Vector3& position, int value) : 
    Atom::Atom(75, position),
    _value(value)
{
    assert(value >=0 && value <= 1);
    Real color = 0.2+8.0*value/10.0;

    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(3),
        ColourValue(color, color, color, 1.0)
    );
}

int Atom_Term_Virt::getValue() const
{
    return _value;
}

bool Atom_Term_Virt::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Term>() ||
        atom->isType<Atom_Term_Virt>();
}

