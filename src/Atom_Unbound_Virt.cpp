#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Unbound_Virt::Atom_Unbound_Virt(const Vector3& position) : 
    Atom::Atom(100, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(3),
        ColourValue(0.5, 1.0, 1.0, 1.0)
    );
}

bool Atom_Unbound_Virt::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Unbound>() ||
        atom->isType<Atom_Unbound_Virt>();
}

Atom* Atom_Unbound_Virt::create() const
{
    return new Atom_Unbound_Virt(_position);
}

