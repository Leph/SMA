#ifndef SIMULATTIONLISTENER_HPP
#define SIMULATIONLISTENER_HPP

#include <Ogre.h>

/**
 * Gestion de la dynamique de la simulation
 * à chaque frames
 */
class SimulationListener : public Ogre::FrameListener
{
    public:
    
    /**
     * Implémente la callback gérant à chaque frame
     * la mise à jour de la simulation
     * FrameListener
     */
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);

    private:
};

#endif

