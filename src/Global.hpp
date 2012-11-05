#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <Ogre.h>

/**
 * Conteneur static pour les instances globales
 */
class Global
{
    public:

        /**
         * Renvoi et définie l'instance globale du scene manager
         * de Ogre
         */
        static Ogre::SceneManager* getSceneManager();
        static void setSceneManager(Ogre::SceneManager* sceneManager);

    private:

        /**
         * Ogre scene manager
         * Instanciée dans Application.cpp
         */
        static Ogre::SceneManager* _sceneManager;
};

#endif

