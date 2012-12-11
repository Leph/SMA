#include "SimulationListener.hpp"
#include "Global.hpp"
#include "Atoms.hpp"
#include "TransformLambda.hpp"

using Ogre::FrameEvent;

SimulationListener::SimulationListener() :
    _transformTimeCount(SimulationListener::TRANSFORM_FREQ),
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

    if (_transformTimeCount <= 0.0) {
        //Cherches des transformations à appliquées
        for (size_t i=0;i<size;i++) {
            if (
                Global::getAtomManager()->get(i)
                    ->isType<Atom_Lambda>() &&
                !Global::getAtomManager()->get(i)
                    ->isFixed()
            ) {
                //Ajoute le graphe si la transformation 
                //est valide
                Graph* graph = new Graph();
                graph->build(Global::getAtomManager()
                    ->get(i));
                Transform* transform = 
                    new TransformLambda(graph);
                if (transform->isValid()) {
                    _transforms.push_back(transform);
                } else {
                    //La désallocation de la transformation
                    //désalloue la graphe
                    delete transform;
                }
            }
        }
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
        //Incrémente le compteur de temps
        _transformTimeCount -= SimulationListener::STEP_TIME;
    }

    return true;
}

