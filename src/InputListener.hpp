#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP

#include <Ogre.h>
#include <OIS/OIS.h>

/**
 * InsputListener
 * Gestion des entrées
 * à chaque frames
 */
class InputListener : public 
    Ogre::FrameListener, 
    Ogre::WindowEventListener, 
    OIS::KeyListener
{
public:

    /**
     * Configuration de la sensibilité du déplacement
     * clavier et sourie de la camera
     */
    Ogre::Real CAMERA_KEYBOARD_VELOCITY;
    Ogre::Real CAMERA_MOUSE_VELOCITY;
    
    /**
     * Construit le gestionaine d'entrée
     * @param window : la fenètre de l'application
     * @param camera : la camera à gérer
     */
    InputListener(Ogre::RenderWindow* window, Ogre::Camera* camera);

    /**
     * Détache l'instance de la gestion des entrées
     */
    ~InputListener();

    /**
     * Implémente la callback de redimentionnement de la fenètre
     * WindowEventListener
     */
    virtual void windowResized(Ogre::RenderWindow* window);

    /**
     * Implémente la callback de fermeture de la fenètre
     * WindowEventListener
     */
    virtual void windowClosed(Ogre::RenderWindow* window);

    /**
     * Implémente la callback de gestion des touches clavier
     * enfoncées
     * KeyListener
     */
    virtual bool keyPressed(const OIS::KeyEvent& e);

    /**
     * Implémente la callback de gestion des touches clavier
     * relachées
     * KeyListener
     */
    virtual bool keyReleased(const OIS::KeyEvent& e);

    /**
     * Implémente la callback gérant à chaque frame les 
     * entrées utilisateurs
     * FrameListener
     */
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);

private:

    /**
     * Ogre window
     */
    Ogre::RenderWindow* _window;

    /**
     * Ogre camera
     */
    Ogre::Camera* _camera;

    /**
     * Gestionnaire d'entré OIS
     */
    OIS::InputManager* _inputManager;

    /**
     * OIS mouse objet
     */
    OIS::Mouse* _mouse;

    /**
     * OIS keyboard objet
     */
    OIS::Keyboard* _keyboard;

    /**
     * Initialise OIS
     */
    void startOIS();
};

#endif

