#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Apply_Virt::Atom_Apply_Virt(Vector3& position) : 
    Atom::Atom(200, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(1.0, 0.5, 0.5, 1.0)
    );
}

bool Atom_Apply_Virt::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Apply>() ||
        atom->isType<Atom_Apply_Virt>();
}

