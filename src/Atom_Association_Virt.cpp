#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Association_Virt::Atom_Association_Virt
    (const Vector3& position) : 
    Atom::Atom(50, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(0.5, 0.5, 1.0, 1.0)
    );
}

bool Atom_Association_Virt::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Association>() ||
        atom->isType<Atom_Association_Virt>();
}

Atom* Atom_Association_Virt::create() const
{
    return new Atom_Association_Virt(_position);
}

