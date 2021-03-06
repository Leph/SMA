#ifndef ATOM_ASSOCIATION_VIRT_HPP
#define ATOM_ASSOCIATION_VIRT_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Association_Virt
 * Représente l'atome de type Association_Virt
 */
class Atom_Association_Virt : public Atom
{
    public:

        Atom_Association_Virt(const Ogre::Vector3& position);

        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

