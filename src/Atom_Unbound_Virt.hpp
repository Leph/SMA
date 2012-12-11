#ifndef ATOM_UNBOUND_VIRT_HPP
#define ATOM_UNBOUND_VIRT_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Unbound_Virt
 * Représente l'atome de type Apply_Unbound_Virt
 */
class Atom_Unbound_Virt : public Atom
{
    public:

        Atom_Unbound_Virt(const Ogre::Vector3& position);
        
        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

