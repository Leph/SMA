#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP

class InputListener : public Ogre::FrameListener
{
public:
    
    /**
     *
     */
    InputListener(Ogre::RenderWindow* window, Ogre::Camera* camera);

private:

    /**
     *
     */
    RenderWindow* _window;

    /**
     *
     */
    Camera* _camera;

    /**
     *
     */
    OIS::InputManager* _inputManager;

    /**
     *
     */
    OIS::Mouse* _mouse;

    /**
     *
     */
    OIS::Keyboard* _keyboard;

    /**
     *
     */
    bool frameRenderingQueued(const Ogre::FrameEvent& event);
};

#endif

