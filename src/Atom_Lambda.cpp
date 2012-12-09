#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Lambda::Atom_Lambda(const Vector3& position) : 
    Atom::Atom(100, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(0.0, 1.0, 0.0, 1.0)
    );
}

bool Atom_Lambda::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Lambda>();
}

Atom* Atom_Lambda::create() const
{
    return new Atom_Lambda(_position);
}

