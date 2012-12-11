#include <assert.h>

#include "Global.hpp"

using Ogre::SceneManager;

/**
 * Initialisation des pointeurs static
 */
SceneManager* Global::_sceneManager = 0;
AtomManager* Global::_atomManager = 0;
PositionResolver* Global::_positionResolver = 0;
Terrain* Global::_terrain = 0;
bool Global::_runSimulation = false;

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

AtomManager* Global::getAtomManager()
{
    assert(Global::_atomManager != 0);
    return Global::_atomManager;
}

void Global::setAtomManager(AtomManager* atomManager)
{
    assert(atomManager != 0);
    Global::_atomManager = atomManager;
}

PositionResolver* Global::getPositionResolver()
{
    assert(Global::_positionResolver != 0);
    return Global::_positionResolver;
}

void Global::setPositionResolver
    (PositionResolver* positionResolver)
{
    assert(positionResolver != 0);
    Global::_positionResolver = positionResolver;
}

Terrain* Global::getTerrain()
{
    assert(Global::_terrain != 0);
    return Global::_terrain;
}

void Global::setTerrain(Terrain* terrain)
{
    assert(terrain != 0);
    Global::_terrain = terrain;
}

bool Global::isRunSimulation()
{
    return _runSimulation;
}
        
bool Global::setRunSimulation(bool run)
{
    _runSimulation = run;
}

