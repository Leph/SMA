#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <Ogre.h>

/**
 * Terrain
 * Repressente le terrain dans lequel évolue les
 * atoms
 * L'instance est Global
 */
class Terrain
{
    public:

        /**
         * Construit et initialise le terrain
         */
        Terrain();
        
        /**
         * Supprime le Node des données d'Ogre
         */
        ~Terrain();

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
         * Le noeud Ogre auquel est rataché la 
         * représentation graphique du terrain
         */
        Ogre::SceneNode* _node;

        /**
         * Créer et initialise le Node Ogre pour
         * la représentation graphique
         */
        void initNode();
};

#endif

