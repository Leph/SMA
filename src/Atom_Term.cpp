#include <assert.h>

#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::Real;
using Ogre::ColourValue;

Atom_Term::Atom_Term(Vector3& position, int value) : 
    Atom::Atom(75, position),
    _value(value)
{
    assert(value >=0 && value <= 1);
    Real color = 0.2+8.0*value/10.0;

    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10),
        ColourValue(color, color, color, 1.0)
    );
}

int Atom_Term::getValue() const
{
    return _value;
}

bool Atom_Term::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Term>();
}

