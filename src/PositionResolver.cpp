#include <assert.h>

#include "PositionResolver.hpp"
#include "Global.hpp"

using Ogre::Vector3;
using Ogre::Real;

Vector3 PositionResolver::resolve
    (const Atom* atom, Vector3 motion) const
{
    assert(atom != 0);

    Vector3 start = atom->getPosition();
    Vector3 stop = start+motion;
    Real radius = atom->getRadius();
   
    //Vérification de la pré contrainte
    assert(Global::getAtomManager()
        ->checkCollisions(start, radius, atom) == false);

    if (
        Global::getAtomManager()
        ->checkCollisions(stop, radius, atom)
    ) {
        //Si la position d'arrivée est déjà
        //occupée, on cherche par dichotomie
        //la meilleur position sans collision
        /*
        for (int i=0;i<5;i++) {
            Vector3 middle = (start+stop)/2.0;
            if (
                Global::getAtomManager()
                ->checkCollisions(middle, radius, atom)
            ) {
                //Si il y a collision, on rapproche le stop
                stop = middle;
            } else {
                //si pas de collision, on avance le start
                start = middle;
            }
        }
        */
        assert(Global::getAtomManager()
            ->checkCollisions(start, radius, atom) == false);
        return start;
    } else {
        //Si il n'y a pas de collision à la position
        //d'arrivée, c'est bon
        assert(Global::getAtomManager()
            ->checkCollisions(stop, radius, atom) == false);
        return stop;
    }
}

