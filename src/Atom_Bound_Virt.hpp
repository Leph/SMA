#ifndef ATOM_BOUND_VIRT_HPP
#define ATOM_BOUND_VIRT_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Bound_Virt
 * Représente l'atome de type Apply_Bound_Virt
 */
class Atom_Bound_Virt : public Atom
{
    public:

        Atom_Bound_Virt(const Ogre::Vector3& position);
        
        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

