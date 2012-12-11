#ifndef ATOM_UNBOUND_HPP
#define ATOM_UNBOUND_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Unbound
 * Représente l'atome de type Unbound
 */
class Atom_Unbound : public Atom
{
    public:

        Atom_Unbound(const Ogre::Vector3& position);

        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

