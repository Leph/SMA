#ifndef ATOM_APPLY_VIRT_HPP
#define ATOM_APPLY_VIRT_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Apply_Virt
 * Représente l'atome de type Apply_Virt
 */
class Atom_Apply_Virt : public Atom
{
    public:

        Atom_Apply_Virt(Ogre::Vector3& position);
        
        virtual bool isRepresent(const Atom* atom) const;
};

#endif

