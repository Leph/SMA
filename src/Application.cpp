#include <Ogre.h>

#include "Application.hpp"

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

Application::Application() : 
    _root(0),
    _window(0),
    _scene(0),
    _camera(0)
//    _inputListener(0)
{
    setup();
}

Application::~Application()
{
    delete _root;
}

void Application::setup()
{
    _root = new Root("plugins.cfg", "ogre.cfg", "Ogre.log");

    loadResources();
    createRenderWindow();
    
    //Chargement des ressources
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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
        std::cout << "RATEEEEEEEEEEEEEEE" << std::endl;
        throw new Exception(
            Exception::ERR_INVALIDPARAMS, 
            "Unable to configure Ogre Application", 
            "Pouet"
        );
    }

    //Création de la fenetre
    _window = _root->initialise(true, "SMA Ogre Project");
}

void Application::createScene()
{
    _scene = _root->createSceneManager("DefaultSceneManager", "scene_manager");
    _scene->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));
}

void Application::createCamera()
{
    _camera = _scene->createCamera("camera");
    _camera->setPosition(Vector3(0,0,100));
    _camera->lookAt(Vector3(0,0,0));
    _camera->setNearClipDistance(1);
    _camera->setFarClipDistance(10000);

    Viewport* vp = _window->addViewport(_camera);
    _camera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    vp->setBackgroundColour(ColourValue(0,0,0));
}

/*void Application::createFrameListener()
{
    _inputListener = new InputListener(_window, _camera);
    _root->addFrameListener(_inputListener);
}*/

void Application::run()
{
    createScene();
    createCamera();

    Entity* ent = _scene->createEntity("ogrehead", "ogrehead.mesh");
    SceneNode* node = _scene->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);

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

