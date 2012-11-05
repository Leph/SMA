#include <assert.h>

#include "Global.hpp"

using Ogre::SceneManager;

/**
 * Initialisation des pointeurs static
 */
SceneManager* Global::_sceneManager = 0;

SceneManager* Global::getSceneManager()
{
    assert(Global::_sceneManager != 0);
    return Global::_sceneManager;
}

void Global::setSceneManager(SceneManager* sceneManager)
{
    assert(sceneManager != 0);
    Global::_sceneManager = sceneManager;
}

