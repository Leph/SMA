#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Bound::Atom_Bound(const Vector3& position) : 
    Atom::Atom(100, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(1.0, 1.0, 0.0, 1.0)
    );
}

bool Atom_Bound::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Bound>();
}

Atom* Atom_Bound::create() const
{
    return new Atom_Bound(_position);
}

