#include "Atom_Association_Virt.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Association_Virt::Atom_Association_Virt
    (Vector3& position) : 
    Atom::Atom(50, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(0.5, 0.5, 1.0, 1.0)
    );
}

