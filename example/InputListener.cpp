#include "InputListener.h"

InputListener::InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera)
{
    _window = wnd;
    _camera = camera;
}

bool InputListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if( _window->isClosed() )
        return false;

    _keyboard->capture();
    _mouse->capture();
 
    if( _keyboard->isKeyDown(OIS::KC_ESCAPE) )
        return false;
 
    return true;
}
