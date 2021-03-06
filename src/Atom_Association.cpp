#include "Atoms.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Association::Atom_Association(const Vector3& position) : 
    Atom::Atom(50, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(0.0, 0.0, 1.0, 1.0)
    );
}

bool Atom_Association::isRepresent(const Atom* atom) const
{
    return 
        atom->isType<Atom_Association>();
}

Atom* Atom_Association::create() const
{
    return new Atom_Association(_position);
}

