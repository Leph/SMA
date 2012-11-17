#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <Ogre.h>
#include "AtomManager.hpp"
#include "PositionResolver.hpp"

/**
 * Conteneur static pour les instances globales
 */
class Global
{
    public:

        /**
         * Renvoi et définie l'instance globale du scene 
         * manager de Ogre
         */
        static Ogre::SceneManager* getSceneManager();
        static void setSceneManager
            (Ogre::SceneManager* sceneManager);

        /**
         * Renvoi et définie l'instance globale du conteneur 
         * des atomes
         */
        static AtomManager* getAtomManager();
        static void setAtomManager(AtomManager* atomManager);

        /**
         * Renvoi et définie l'instance globale du gestionaire
         * de collision
         */
        static PositionResolver* getPositionResolver();
        static void setPositionResolver
            (PositionResolver* positionResolver);

    private:

        /**
         * Ogre scene manager
         * Instanciée dans Application.cpp
         */
        static Ogre::SceneManager* _sceneManager;

        /**
         * AtomManager
         * Conteneur de tous les atoms
         */
        static AtomManager* _atomManager;
        
        /**
         * PositionResolver
         * Gestion des collisions et contraintes
         * spaciales
         */
        static PositionResolver* _positionResolver;
};

#endif

