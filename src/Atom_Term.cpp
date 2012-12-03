#include "Atom_Term.hpp"
#include "Geometry.hpp"

using Ogre::Vector3;
using Ogre::ColourValue;

Atom_Term::Atom_Term(Vector3& position) : 
    Atom::Atom(75, position)
{
    //Création de l'apparence graphique de l'atome
    initNode(
        Geometry::sphere(10), 
        ColourValue(1.0, 1.0, 1.0, 1.0)
    );
}

