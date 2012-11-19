#include "SimulationListener.hpp"
#include "Global.hpp"

using Ogre::FrameEvent;

bool SimulationListener::frameRenderingQueued(const FrameEvent& event)
{
    Global::getAtomManager()->shuffle();
    size_t size = Global::getAtomManager()->getSize();
    size_t i;
    for (i=0;i<size;i++) {
        Global::getAtomManager()->get(i)->move(1.0);
    }

    return true;
}

