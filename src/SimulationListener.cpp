#include "SimulationListener.hpp"
#include "Global.hpp"

using Ogre::FrameEvent;

bool SimulationListener::frameRenderingQueued(const FrameEvent& event)
{
    std::cout << Global::getAtomManager()->getSize() << std::endl;
    if (Global::getAtomManager()->getSize() == 2) {
        return true;
    }

    Global::getAtomManager()->shuffle();
    size_t size = Global::getAtomManager()->getSize();
    size_t i;
    for (i=0;i<size;i++) {
        Global::getAtomManager()->get(i)->move(0.1);
        std::cout << "> " << Global::getAtomManager()->get(i) << "    ";
        std::cout << Global::getAtomManager()->get(i)->getPosition().x << " ";
        std::cout << Global::getAtomManager()->get(i)->getPosition().y << " ";
        std::cout << Global::getAtomManager()->get(i)->getPosition().z << " ";
        std::cout << Global::getAtomManager()->get(i)->getRadius() << std::endl;
        for (size_t j=0;j<size;j++) {
            std::cout << Global::getAtomManager()->get(j) << "    ";
            std::cout << Global::getAtomManager()->get(j)->getPosition().x << " ";
            std::cout << Global::getAtomManager()->get(j)->getPosition().y << " ";
            std::cout << Global::getAtomManager()->get(j)->getPosition().z << " ";
            std::cout << Global::getAtomManager()->get(j)->getRadius() << std::endl;
            if(Global::getAtomManager()
                ->checkCollisions(Global::getAtomManager()->get(j)->getPosition(), Global::getAtomManager()->get(j)->getRadius(), Global::getAtomManager()->get(j)) == true) {
                std::cout << "pouet1" << std::endl;
                for (size_t k=0;k<size;k++) {
                    if (k!=i && k!=j) {
                        Global::getAtomManager()->remove(k);
                    }
                }
                std::cout << "pouet2" << std::endl;
                Global::getAtomManager()->shuffle();
                std::cout << "pouet3" << std::endl;
                return true;
            }
        }
    }

    return true;
}

