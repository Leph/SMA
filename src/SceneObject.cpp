#include <Ogre.h>

#include "SceneObject.hpp"
#include "Global.hpp"

SceneObject::SceneObject() :
    _node(0),
    _manual(0)
{
}

SceneObject::~SceneObject()
{
    clearSceneObject();
}

void SceneObject::clearSceneObject()
{
    //Détruit la manualObject
    if (_manual != 0) {
        Global::getSceneManager()
            ->destroyManualObject(_manual);
        _manual = 0;
    }
    //Détruit le noeud de scene
    if (_node != 0) {
        _node->removeAllChildren();
        Global::getSceneManager()
            ->destroySceneNode(_node);
        _node = 0;
    }
}

