#include <Ogre.h>

#include "InputListener.h"

using namespace Ogre;

class Application
{
public:
    Application();
    ~Application();

    void start();

private:
    Root* _root;
    RenderWindow* _window;
    SceneManager* _scene;
    Camera* _camera;
    InputListener* _inputListener;

    void openRessources();
    bool setup();
    void createMainWindow();
    void initScene();

    void createFrameListener();
};
