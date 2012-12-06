#ifndef ATOM_TERM_VIRT_HPP
#define ATOM_TERM_VIRT_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Term_Virt
 * Représente l'atome de type Term_Virt
 */
class Atom_Term_Virt : public Atom
{
    public:

        /**
         * Construit l'atome terme avec sa valeur
         */
        Atom_Term_Virt(Ogre::Vector3& position, int value);

        /**
         * Renvoi la valeur du terme
         */
        int getValue() const;

        virtual bool isRepresent(const Atom* atom) const;

    private:

        /**
         * La valeur du terme
         */
        int _value;
};

#endif

