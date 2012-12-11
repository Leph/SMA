#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Bound_Virt::Atom_Bound_Virt(const Vector3& position) : 
    Atom::Atom(100, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(3), 
        ColourValue(1.0, 1.0, 0.5, 1.0)
    );
}

bool Atom_Bound_Virt::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Bound>() ||
        atom->isType<Atom_Bound_Virt>();
}

Atom* Atom_Bound_Virt::create() const
{
    return new Atom_Bound_Virt(_position);
}

