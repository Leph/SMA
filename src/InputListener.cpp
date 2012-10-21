#include <Ogre.h>
#include <OIS/OIS.h>

#include "InputListener.h"

using Ogre::RenderWindow;
using Ogre::Camera;

InputListener::InputListener(RenderWindow* window, Camera* camera)
{
    _window = window;
    _camera = camera;
}

bool InputListener::frameRenderingQueued(const Ogre::FrameEvent& event)
{
    if( _window->isClosed() )
        return false;

    _keyboard->capture();
    _mouse->capture();
 
    if( _keyboard->isKeyDown(OIS::KC_ESCAPE) )
        return false;
 
    return true;
}
