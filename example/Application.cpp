#include "Application.h"


Application::Application() : _root(0)
{
  setup();
}
Application::~Application()
{
    delete _root;
}

void Application::openRessources()
{
    //Chargement des ressources
    ConfigFile configFile;
    configFile.load("resources.cfg");

    //Parcoure du fichier ressource/conf
    ConfigFile::SectionIterator seci = configFile.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
        }
    }
}

void Application::createMainWindow()
{
    //Chargement du moteur avec la config retenu
    if(!(_root->restoreConfig() || _root->showConfigDialog()))
    {
      exit(1);
    }

    //creation de la fenetre d enotre applciation
    _window = _root->initialise( true );
}

bool Application::setup()
{
    //Creation de la racine
    _root = new Root("plugins.cfg", "ogre.cfg", "Ogre.log");

    openRessources();
    createMainWindow();
    
    //Chargement des ressource (textures etc..)
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

   return true;
}

void Application::createFrameListener()
{
  _inputListener = new InputListener( _window, _camera);
  _root->addFrameListener( _inputListener);
}
void Application::initScene()
{
   //Creation de la scene
    _scene = _root->createSceneManager("DefaultSceneManager", "Mon Scene Manager");
    _scene->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    _camera = _scene->createCamera("PlayerCam");
    _camera->setPosition(Vector3(0,0,100));
    _camera->lookAt(Vector3(0,0,0));
    _camera->setNearClipDistance(5);

    Viewport* vp = _window->addViewport( _camera );
    vp->setBackgroundColour( ColourValue(0,0,0) );
    _camera->setAspectRatio( Real(vp->getActualWidth()) / Real(vp->getActualHeight()) );

    Entity *ent = _scene->createEntity( "ogrehead", "ogrehead.mesh" );
    SceneNode *node = _scene->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}

void Application::start()
{
  
  initScene();
 //boucle infinie
  while(true)
    {
      WindowEventUtilities::messagePump();
      
      if(_window->isClosed())
        return ;
      
      if(!_root->renderOneFrame())
        return ;
    }
  
}
