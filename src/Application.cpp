#include "Application.hpp"
#include "Global.hpp"
#include "Atom.hpp"

using Ogre::Root;
using Ogre::String;
using Ogre::ConfigFile;
using Ogre::ResourceGroupManager;
using Ogre::TextureManager;
using Ogre::ColourValue;
using Ogre::Exception;
using Ogre::Vector3;
using Ogre::Viewport;
using Ogre::Real;
using Ogre::Entity;
using Ogre::SceneNode;
using Ogre::WindowEventUtilities;
using Ogre::Math;

Application::Application() : 
    _root(0),
    _window(0),
    _scene(0),
    _camera(0),
    _inputListener(0),
    _simulationListener(0),
    _atoms(0),
    _positionResolver(0)
{
    setup();
}

Application::~Application()
{
    delete _positionResolver;
    delete _atoms;
    delete _root;
}

void Application::setup()
{
    //Création de l'objet racine principale
    _root = new Root("plugins.cfg", "ogre.cfg", "Ogre.log");

    loadResources();
    createRenderWindow();
    createScene();
    createCamera();
    createFrameListener();
    
    //Chargement des ressources
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    //Création et enregistrement global du conteneur d'atome
    _atoms = new AtomManager();
    Global::setAtomManager(_atoms);
    
    //Création et enregistrement globlal du gestionnaire
    //de collisions
    _positionResolver = new PositionResolver();
    Global::setPositionResolver(_positionResolver);
}

void Application::loadResources()
{
    //Chargement de la configuration
    ConfigFile configFile;
    configFile.load("resources.cfg");

    //Lecture des ressources
    ConfigFile::SectionIterator seci = configFile.getSectionIterator();
    String secName, typeName, archName;
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); i++) {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().
                addResourceLocation(archName, typeName, secName);
        }
    }
}

void Application::createRenderWindow()
{
    //Chargement de la configuration
    if(!_root->restoreConfig() && !_root->showConfigDialog()) {
        throw new Exception(
            Exception::ERR_INVALIDPARAMS, 
            "Unable to configure Ogre Application", 
            ""
        );
    }

    //Création de la fenetre
    _window = _root->initialise(true, "SMA Ogre Project");
}

void Application::createScene()
{
    //Création et choix du scene manager : Octree
    _scene = _root->createSceneManager("OctreeSceneManager");

    //Défini le scene manager comme global
    Global::setSceneManager(_scene);
}

void Application::createCamera()
{
    _camera = _scene->createCamera("camera");
    _camera->setPosition(Vector3(0,0,100));
    _camera->lookAt(Vector3(0,0,0));
    _camera->setNearClipDistance(1);
    _camera->setFarClipDistance(10000);

    Viewport* vp = _window->addViewport(_camera);
    _camera->setAspectRatio(Real(vp->getActualWidth())/Real(vp->getActualHeight()));
    _camera->setPolygonMode(Ogre::PM_WIREFRAME);
    vp->setBackgroundColour(ColourValue(0,0,0));
}

void Application::createFrameListener()
{
    //Gestion des entrées
    _inputListener = new InputListener(_window, _camera);
    _root->addFrameListener(_inputListener);

    //Gestion de la simulation
    _simulationListener = new SimulationListener();
    _root->addFrameListener(_simulationListener);
}

void Application::run()
{
    //Initialisation de la scene etde la simulation
    initSimulation();

    //Boucle de rendu
    while(true)
    {
        WindowEventUtilities::messagePump();
        if(_window->isClosed()) {
            return;
        }
        if(!_root->renderOneFrame()) {
            return ;
        }
    }
}

void Application::initSimulation()
{
    _scene->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
    Ogre::Light *light1 = _scene->createLight();
    light1->setDiffuseColour(1.0, 0.7, 1.0);
    light1->setSpecularColour(1.0, 0.7, 1.0);
    light1->setPosition(-100, 200, 100);

    Entity* ent = _scene->createEntity("ogrehead.mesh");
    SceneNode* node = _scene->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);

    for (int i=0;i<500;i++) {
        Vector3 position = Vector3(
            Math::RangeRandom(-1000, 1000),
            Math::RangeRandom(-1000, 1000),
            Math::RangeRandom(-1000, 1000));
        Real radius = Math::RangeRandom(50, 100);
        if (!_atoms->checkCollisions(position, radius, 0)) {
            Atom* a = new Atom(radius, position);
            _atoms->add(a);
            //Mise à jour du graphe de scene
            _scene->_updateSceneGraph(0);
        }
    }
}

