#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <Ogre.h>

/**
 * Geometry
 *
 * Factorise la création manuel de mesh
 * (Ogre manual object)
 */
class Geometry
{
    public:

        /**
         * Renvoi le mesh du terrain
         */
        static Ogre::ManualObject* terrain
            (Ogre::Real subdivision);

        /**
         * Renvoi le mesh d'un cylindre
         * le long de l'axe X
         */
        static Ogre::ManualObject* cylinder
            (Ogre::Real subdivision);

        /**
         * Renvoi le mesh d'un diament
         */
        static Ogre::ManualObject* diamond();

        /**
         * Renvoi le mesh d'une sphere
         */
        static Ogre::ManualObject* sphere
            (Ogre::Real subdivision);
};

#endif

