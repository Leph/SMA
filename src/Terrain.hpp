#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <Ogre.h>
#include "SceneObject.hpp"

/**
 * Terrain
 * Repressente le terrain dans lequel évolue les
 * atoms
 * L'instance est Global
 */
class Terrain : public SceneObject
{
    public:

        /**
         * Construit et initialise le terrain
         */
        Terrain();
        
        /**
         * Renvoi true si la sphere spéficiée entre en
         * collision avec les bords du terrain
         */
        bool checkCollision(const Ogre::Vector3& position, 
            Ogre::Real radius) const;

    private:

        /**
         * La taille du cube centré sur l'origine
         */
        Ogre::Real _size;

        /**
         * Le nombre de subdivision pour le rendu graphique
         */
        Ogre::Real _subdivision;
        
        /**
         * Créer et initialise le Node Ogre pour
         * la représentation graphique
         */
        void initNode();
};

#endif

