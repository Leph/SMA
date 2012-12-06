#ifndef ATOM_TERM_VIRT_HPP
#define ATOM_TERM_VIRT_HPP

#include <Ogre.h>
#include "Atom_Term.hpp"

/**
 * Atom_Term_Virt
 * Représente l'atome de type Term_Virt
 */
class Atom_Term_Virt : public Atom_Term
{
    public:

        Atom_Term_Virt(Ogre::Vector3& position, int value);
};

#endif

