#include "Atom_Association.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Association::Atom_Association(Vector3& position) : 
    Atom::Atom(50, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(0.0, 0.0, 1.0, 1.0)
    );
}

