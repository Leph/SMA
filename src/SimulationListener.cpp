#include "SimulationListener.hpp"
#include "Global.hpp"
#include "Atoms.hpp"

using Ogre::FrameEvent;

SimulationListener::SimulationListener() :
    _transformTimeCount(SimulationListener::TRANSFORM_FREQ),
    _transformSearchTimeCount(
        SimulationListener::TRANSFORM_SEARCH_FREQ),
    _transforms()
{
}

bool SimulationListener::frameRenderingQueued
    (const FrameEvent& event)
{
    //Controle l'activation de la simulation
    if (!Global::isRunSimulation()) {
        return true;
    }

    //Mélange le conteneur d'atome
    Global::getAtomManager()->shuffle();
    size_t size = Global::getAtomManager()->getSize();

    //Déplace les atomes
    for (size_t i=0;i<size;i++) {
        Global::getAtomManager()->get(i)
            ->move(SimulationListener::STEP_TIME);
    }

    //Cherches des transformations à appliquées
    if (_transformSearchTimeCount <= 0.0) {
        for (size_t i=0;i<size;i++) {
            Transform* transform = 0;
            if (
                (transform = Transform::
                    checkAndCreate<TransformLambda>(
                    Global::getAtomManager()->get(i)))
                != 0
            ) {
                //Lambda
                _transforms.push_back(transform);
            } else if (
                (transform = Transform::
                    checkAndCreate<TransformBound>(
                    Global::getAtomManager()->get(i)))
                != 0
            ) {
                //Bound
                _transforms.push_back(transform);
            } else if (
                (transform = Transform::
                    checkAndCreate<TransformUnbound>(
                    Global::getAtomManager()->get(i)))
                != 0
            ) {
                //Unbound
                _transforms.push_back(transform);
            }
        }
        //Reset le compteur de temps
        _transformSearchTimeCount = 
            SimulationListener::TRANSFORM_SEARCH_FREQ;
    } else {
        //Décrémente le compteur de temps
        _transformSearchTimeCount -= 
            SimulationListener::STEP_TIME;
    }
    if (_transformTimeCount <= 0.0) {
        //Avance d'une étape toutes les transformations 
        //en cours
        //et supprime les transformations finies
        size_t j = 0;
        while (j < _transforms.size()) {
            bool isContinued = _transforms[j]
                ->doTransformStep();
            if (!isContinued) {
                delete _transforms[j];
                _transforms[j] = 
                    _transforms[_transforms.size()-1];
                _transforms.pop_back();
            }
            j++;
        }
        //Reset le compteur de temps
        _transformTimeCount = 
            SimulationListener::TRANSFORM_FREQ;
    } else {
        //Décrémente le compteur de temps
        _transformTimeCount -= SimulationListener::STEP_TIME;
    }

    return true;
}

