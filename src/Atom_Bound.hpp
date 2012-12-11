#ifndef ATOM_BOUND_HPP
#define ATOM_BOUND_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Bound
 * Représente l'atome de type Bound
 */
class Atom_Bound : public Atom
{
    public:

        Atom_Bound(const Ogre::Vector3& position);

        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

