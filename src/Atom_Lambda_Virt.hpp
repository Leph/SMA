#ifndef ATOM_LAMBDA_VIRT_HPP
#define ATOM_LAMBDA_VIRT_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Lambda_Virt
 * Représente l'atome de type Lambda_Virt
 */
class Atom_Lambda_Virt : public Atom
{
    public:

        Atom_Lambda_Virt(const Ogre::Vector3& position);

        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

