#ifndef ATOM_LAMBDA_HPP
#define ATOM_LAMBDA_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Lambda
 * Représente l'atome de type Lambda
 */
class Atom_Lambda : public Atom
{
    public:

        Atom_Lambda(const Ogre::Vector3& position);

        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

