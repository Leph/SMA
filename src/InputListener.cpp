#include "InputListener.hpp"

using Ogre::RenderWindow;
using Ogre::Camera;
using Ogre::FrameEvent;
using Ogre::Real;
using Ogre::Degree;
using Ogre::Vector3;
using Ogre::WindowEventUtilities;
using OIS::ParamList;
using OIS::InputManager;
using OIS::Keyboard;
using OIS::Mouse;
using OIS::MouseState;
using OIS::KeyEvent;

InputListener::InputListener(RenderWindow* window, Camera* camera) :
    _window(window),
    _camera(camera),
    _inputManager(0),
    _mouse(0),
    _keyboard(0)
{
    //Paramètre de configuration
    CAMERA_KEYBOARD_VELOCITY = 200;
    CAMERA_MOUSE_VELOCITY = 50;

    //Initialisation de la gestion des entrées
    startOIS();
}

InputListener::~InputListener()
{
    WindowEventUtilities::removeWindowEventListener(_window, this);
    windowClosed(_window);
}

void InputListener::windowResized(RenderWindow* window)
{
    unsigned int width, height, depth;
    int left, top;
    window->getMetrics(width, height, depth, left, top);

    //Mise à jour de la taille de la fenètre pour le calcul
    //de la position de la sourie
    const MouseState& ms = _mouse->getMouseState();
    ms.width = width;
    ms.height = height;

    //Met à jour le ratio de la vue de la camera
    _camera->setAspectRatio(Real(width)/Real(height));
}
    
void InputListener::windowClosed(RenderWindow* window)
{
    if(window == _window) {
        if(_inputManager) {
            _inputManager->destroyInputObject(_mouse);
            _inputManager->destroyInputObject(_keyboard);
            InputManager::destroyInputSystem(_inputManager);
            _inputManager = 0;
        }
    }
}
    
bool InputListener::keyPressed(const OIS::KeyEvent& e)
{
    return true;
}

bool InputListener::keyReleased(const OIS::KeyEvent& e)
{
    return true;
}

bool InputListener::frameRenderingQueued(const FrameEvent& event)
{
    //Test la fermeture de la fenètre
    if(_window->isClosed()) {
        return false;
    }

    //Récupère les évènement des entrées
    _keyboard->capture();
    _mouse->capture();
 
    //Gère la réponse aux évènements clavier
    if(_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
        return false;
    }
    if (_keyboard->isKeyDown(OIS::KC_Z)) {
        _camera->moveRelative(
            Vector3(0, 0, -CAMERA_KEYBOARD_VELOCITY*event.timeSinceLastFrame));
    }
    if (_keyboard->isKeyDown(OIS::KC_S)) {
        _camera->moveRelative(
            Vector3(0, 0, CAMERA_KEYBOARD_VELOCITY*event.timeSinceLastFrame));
    }
    if (_keyboard->isKeyDown(OIS::KC_Q)) {
        _camera->moveRelative(
            Vector3(-CAMERA_KEYBOARD_VELOCITY*event.timeSinceLastFrame, 0, 0));
    }
    if (_keyboard->isKeyDown(OIS::KC_D)) {
        _camera->moveRelative(
            Vector3(CAMERA_KEYBOARD_VELOCITY*event.timeSinceLastFrame, 0, 0));
    }
    
    //Gère la réponse aux évènements sourie
    const MouseState& ms = _mouse->getMouseState();
    _camera->yaw(
        Degree(-CAMERA_MOUSE_VELOCITY*ms.X.rel*event.timeSinceLastFrame));
    _camera->pitch(
        Degree(-CAMERA_MOUSE_VELOCITY*ms.Y.rel*event.timeSinceLastFrame));
 
    return true;
}

void InputListener::startOIS()
{
    //Récupération de l'identifiant de la fenètre
    ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    _window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    //Création du gestionnaire d'évènement
    _inputManager = InputManager::createInputSystem(pl);

    //Création des objets clavier et sourie
    _keyboard = static_cast<Keyboard*>
        (_inputManager->createInputObject(OIS::OISKeyboard, true));
    _mouse = static_cast<Mouse*>
        (_inputManager->createInputObject(OIS::OISMouse, true));

    //Attache l'instance au gestionnaire d'évènement de la fenètre
    windowResized(_window);
    WindowEventUtilities::addWindowEventListener(_window, this);

    //Attache l'instance au gestionnaire d'évènement du clavier
    _keyboard->setEventCallback(this);
}

