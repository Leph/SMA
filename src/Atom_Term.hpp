#ifndef ATOM_TERM_HPP
#define ATOM_TERM_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Term
 * Représente l'atome de type Term
 */
class Atom_Term : public Atom
{
    public:

        /**
         * Construit l'atome terme avec sa valeur
         */
        Atom_Term(Ogre::Vector3& position, int value);

        /**
         * Renvoi la valeur du terme
         */
        int getValue() const;

    private:

        /**
         * La valeur du terme
         */
        int _value;
};

#endif

