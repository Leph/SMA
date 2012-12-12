#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <Ogre.h>

/**
 * Class SceneObject
 * Factorise l'utilisation de sceneNode Ogre
 * avec des manualObject
 */
class SceneObject
{
    public:

        /**
         * Initialise les pointeurs
         */
        SceneObject();

        /**
         * Désalloue les object d'Ogre
         */
        virtual ~SceneObject();

        /**
         * Désalloue les object d'Ogre
         */
        void clearSceneObject();

    protected:
        
        /**
         * Le noeud Ogre auquel est rataché la 
         * représentation graphique de l'objet
         */
        Ogre::SceneNode* _node;

        /**
         * Le manualObject utilisé pour
         * desinner l'objet
         */
        Ogre::ManualObject* _manual;
};

#endif

