#ifndef POSITIONRESOLVER_HPP
#define POSITIONRESOLVER_HPP

#include <Ogre.h>
#include "Atom.hpp"

/**
 * PositionResolver
 * Cette classe permet de gerer les contraintes
 * de position des atoms. Résolution des collisions
 * et placement dans l'espace
 */
class PositionResolver
{
    public:

        /**
         * Renvoi la nouvelle position de l'atome
         * donné et se déplaçant du vecteur
         * motion en tenant compte de toutes les 
         * collisions avec les autres atomes
         */
        Ogre::Vector3 resolve
            (const Atom* atom, Ogre::Vector3 motion) const;

    private:

};

#endif

