#ifndef SIMULATTIONLISTENER_HPP
#define SIMULATIONLISTENER_HPP

#include <vector>
#include <Ogre.h>
#include "Graph.hpp"
#include "Transform.hpp"

/**
 * Gestion de la dynamique de la simulation
 * à chaque frames
 */
class SimulationListener : public Ogre::FrameListener
{
    public:

        /**
         * Initialise la boucle
         * de simulation
         */
        SimulationListener();
    
        /**
         * Implémente la callback gérant à chaque frame
         * la mise à jour de la simulation
         * FrameListener
         */
        virtual bool frameRenderingQueued
            (const Ogre::FrameEvent& event);

    private:

        /**
         * Pas de temps de la simulation
         * La simulation avance de STEP_TIME à chaque tour
         * de boucle
         */
        static const Ogre::Real STEP_TIME = 1.0;

        /**
         * Temps entre deux application des transformation
         * Les transformations sont appliquées tous les
         * TRANSFORM_FREQ/STEP_TIME tours de boucle
         */
        static const Ogre::Real TRANSFORM_FREQ = 10.0;

        /**
         * Compteur de temps pour l'application
         * des transformation
         * Les transformations sont appliquées quand le
         * compteur atteint 0
         */
        Ogre::Real _transformTimeCount;

        /**
         * Container des transformations 
         * en cours d'executions
         */
        std::vector<Transform*> _transforms;

    
};

#endif

