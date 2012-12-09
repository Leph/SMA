#ifndef ATOM_ASSOCIATION_HPP
#define ATOM_ASSOCIATION_HPP

#include <Ogre.h>
#include "Atoms.hpp"

/**
 * Atom_Association
 * Représente l'atome de type Association
 */
class Atom_Association : public Atom
{
    public:

        Atom_Association(const Ogre::Vector3& position);
        
        virtual bool isRepresent(const Atom* atom) const;
        
        virtual Atom* create() const;
};

#endif

