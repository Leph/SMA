#include <Ogre.h>
#include <OIS/OIS.h>

using namespace Ogre;

class InputListener : public FrameListener
{
public:
  InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera);
  

private:
    RenderWindow* _window;
    Camera*       _camera;

    OIS::InputManager*  _inputManager;
    OIS::Mouse*         _mouse;
    OIS::Keyboard*      _keyboard;
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

};
