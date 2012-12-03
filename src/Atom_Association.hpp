#ifndef ATOM_ASSOCIATION_HPP
#define ATOM_ASSOCIATION_HPP

#include <Ogre.h>
#include "Atom.hpp"

/**
 * Atom_Association
 * Représente l'atome de type Association
 */
class Atom_Association : public Atom
{
    public:

        Atom_Association(Ogre::Vector3& position);
};

#endif

