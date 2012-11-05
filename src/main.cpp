#include <cstdlib>
#include <Ogre.h>

#include "Application.hpp"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
{
    //Initialisation le générateur aléatoire
    srand(0);

    //Créer et lance l'application
    Application app;
    try {
        app.run();
    } catch(Ogre::Exception& e) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }

    return 0;
}
