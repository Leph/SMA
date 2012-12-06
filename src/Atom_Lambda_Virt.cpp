#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Lambda_Virt::Atom_Lambda_Virt(Vector3& position) : 
    Atom::Atom(100, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(0.5, 1.0, 0.5, 1.0)
    );
}

bool Atom_Lambda_Virt::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Lambda>() ||
        atom->isType<Atom_Lambda_Virt>();
}

