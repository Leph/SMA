#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Apply::Atom_Apply(Vector3& position) : 
    Atom::Atom(200, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(1.0, 0.0, 0.0, 1.0)
    );
}

bool Atom_Apply::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Apply>();
}

