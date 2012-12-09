#include "Application.hpp"
#include "Atoms.hpp"
#include "Global.hpp"
#include "Graph.hpp"
#include "TransformLambda.hpp"

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
    _positionResolver(0),
    _terrain(0)
{
    setup();
}

Application::~Application()
{
    delete _positionResolver;
    delete _atoms;
    delete _terrain;
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
    
    //Création et enregistrement global du terrain
    _terrain = new Terrain();
    Global::setTerrain(_terrain);

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
    //_camera->setPolygonMode(Ogre::PM_WIREFRAME);
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
    //Initialisation de la scene et de la simulation
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
    //Initialisation le générateur aléatoire
    //(debug)
    //int seed = (int)Math::RangeRandom(20, 10000000);
    //std::cout << "===>" << (int)seed << std::endl;
    int seed = 6486951;//7264745 8983653;
    //int seed = 7264745;
    //int seed = 8983653;
    srand(seed);

    _scene->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
    Ogre::Light *light1 = _scene->createLight();
    light1->setDiffuseColour(1.0, 1.0, 1.0);
    light1->setSpecularColour(1.0, 1.0, 1.0);
    light1->setPosition(-100, 200, 100);

    Entity* ent = _scene->createEntity("ogrehead.mesh");
    SceneNode* node = _scene->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);

    for (int i=0;i<150;i++) {
        Vector3 position = Vector3(
            Math::RangeRandom(-1500, 1500),
            Math::RangeRandom(-1500, 1500),
            Math::RangeRandom(-1500, 1500));
        Atom* a;
        Real r = Math::RangeRandom(0,100);
        if (r>=90) a = new Atom_Lambda(position);
        else if (r>=80) a = new Atom_Lambda_Virt(position);
        else if (r>=70) a = new Atom_Apply(position);
        else if (r>=60) a = new Atom_Apply_Virt(position);
        else if (r>=50) a = new Atom_Association(position);
        else if (r>=40) a = new Atom_Association_Virt(position);
        else if (r>=20) a = new Atom_Term(
            position, 
            (int)Math::RangeRandom(0.0, 2.0)
        );
        else if (r>=0) a = new Atom_Term_Virt(
            position, 
            (int)Math::RangeRandom(0.0, 2.0)
        );
        if (!_positionResolver->checkCollisionAtoms(
            a->getPosition(), a->getRadius())) 
        {
            _atoms->add(a);
            _scene->_updateSceneGraph(0);
        } else {
            delete a;
        }
    }

    _atoms->createBond(
        _atoms->get(0),
        _atoms->get(1),
        150
    );
    _atoms->createBond(
        _atoms->get(1),
        _atoms->get(2),
        150
    );
    _atoms->createBond(
        _atoms->get(2),
        _atoms->get(3),
        150
    );
    _atoms->createBond(
        _atoms->get(3),
        _atoms->get(0),
        150
    );

    Graph* g = 0;
    for (size_t i=0;i<_atoms->getSize();i++) {
        if (_atoms->get(i)->isType<Atom_Lambda>()) {
            g = new Graph();
            g->build(_atoms->get(i));
            break;
        }
    }
    TransformLambda t = TransformLambda(*g);
    std::cout << t.isValid() << std::endl;
    while(t.doTransformStep());
}

