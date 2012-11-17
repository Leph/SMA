#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Ogre.h>
#include "InputListener.hpp"
#include "SimulationListener.hpp"
#include "AtomManager.hpp"
#include "PositionResolver.hpp"

/**
 * Classe principale représentant l'application Ogre
 */
class Application
{
public:

    /**
     * Construit et initialise 
     * l'application Ogre
     */
    Application();

    /**
     * Détruit l'application
     */
    ~Application();

    /**
     * Lance et execute l'application
     * @throw Ogre::Exception
     */
    void run();

private:
    /**
     * Objet principal d'Ogre
     */
    Ogre::Root* _root;

    /**
     * Ogre window object
     */
    Ogre::RenderWindow* _window;

    /**
     * Ogre scene manager
     */
    Ogre::SceneManager* _scene;

    /**
     * Scene camera
     */
    Ogre::Camera* _camera;

    /**
     * Gestion des entrées utilisateurs
     */
    InputListener* _inputListener;

    /**
     * Gestion de la simulation
     */
    SimulationListener* _simulationListener;

    /**
     * Conteneur des atomes
     */
    AtomManager* _atoms;

    /**
     * Gère les collisions
     */
    PositionResolver* _positionResolver;

    /**
     * Initialisation l'application
     */
    void setup();

    /**
     * Lecture du fichier de configuration
     * "resources.cfg" et chargement des ressources
     */
    void loadResources();

    /**
     * Lecture du fichier de configuration
     * "Ogre.cfg" et chargement du système de rendu
     */
    void createRenderWindow();

    /**
     * Création et initialisation de la scène
     */
    void createScene();

    /**
     * Création et initialisation de la camera
     */
    void createCamera();

    /**
     * Création et initialisation de la gestion des inputs
     */
    void createFrameListener();

    /**
     * Initialisation de la simulation et la scene
     */
    void initSimulation();
};

#endif

