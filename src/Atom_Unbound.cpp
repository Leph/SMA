#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Unbound::Atom_Unbound(const Vector3& position) : 
    Atom::Atom(100, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(0.0, 1.0, 1.0, 1.0)
    );
}

bool Atom_Unbound::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Unbound>();
}

Atom* Atom_Unbound::create() const
{
    return new Atom_Unbound(_position);
}

