#ifndef ATOM_APPLY_HPP
#define ATOM_APPLY_HPP

#include <Ogre.h>
#include "Atom.hpp"

/**
 * Atom_Apply
 * Représente l'atome de type Apply
 */
class Atom_Apply : public Atom
{
    public:

        Atom_Apply(Ogre::Vector3& position);
};

#endif

