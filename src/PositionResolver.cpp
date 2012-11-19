#include <assert.h>
#include <Plugins/OctreeSceneManager/OgreOctreeSceneManager.h>

#include "PositionResolver.hpp"
#include "Global.hpp"

using Ogre::Vector3;
using Ogre::Real;
using Ogre::AxisAlignedBox;
using Ogre::AxisAlignedBoxSceneQuery;
using Ogre::SceneQueryResult;
using Ogre::Any;

PositionResolver::PositionResolver() :
    _query(0),
    _resultQuery()
{
    //Création de la requète de scene
    _query = Global::getSceneManager()
        ->createAABBQuery(
            AxisAlignedBox(),
            Ogre::OctreeSceneManager::ENTITY_TYPE_MASK
        );
}

PositionResolver::~PositionResolver()
{
    //Destruction de la requète de scene
    Global::getSceneManager()->destroyQuery(_query);
}

std::list<Atom*>& PositionResolver::findAtoms(
    const Vector3& center, Real radius, const Atom* exclude)
{
    //Définie la nouvelle requète
    _query->setBox(
        AxisAlignedBox(center-radius, center+radius));
    
    //Suppresion des anciens résultats
    _resultQuery.clear();

    //Requète (Octree)
    SceneQueryResult& result = _query->execute();

    //Récupération et filtrage des résultats
    while (!result.movables.empty()) {
        Any any = result.movables.front()
            ->getUserObjectBindings().getUserAny();
        if (!any.isEmpty()) {
            Atom* atom = Ogre::any_cast<Atom*>(any);
            if (atom != 0 && atom != exclude) {
                //Raffine la détection directement
                //par calcul des distances
                Real distance = atom->getPosition()
                    .squaredDistance(center)
                    - (atom->getRadius()+radius)
                    *(atom->getRadius()+radius);
                if (distance <= 0) {
                    _resultQuery.push_front(atom);
                }
            }
        }
        result.movables.pop_front();
    }

    return _resultQuery;
}

bool PositionResolver::checkCollisionAtoms
    (const Vector3& center, Real radius, const Atom* exclude)
{
    return !findAtoms(center, radius, exclude).empty();
}

Vector3 PositionResolver::resolve
    (const Atom* atom, const Vector3& motion)
{
    assert(atom != 0);

    Vector3 start = atom->getPosition();
    Vector3 stop = start+motion;
   
    //Vérification de la pré contrainte
    assert(positionConstrained(start, atom));

    if (!positionConstrained(stop, atom)) {
        //Si la position d'arrivée est déjà
        //occupée, on cherche par dichotomie
        //la meilleur position sans collision
        for (int i=0;i<4;i++) {
            Vector3 middle = (start+stop)/2.0;
            if (!positionConstrained(middle, atom)) {
                //Si il y a collision, on rapproche le stop
                stop = middle;
            } else {
                //si pas de collision, on avance le start
                start = middle;
            }
        }
        return start;
    } else {
        //Si il n'y a pas de collision à la position
        //d'arrivée, c'est bon
        return stop;
    }
}

bool PositionResolver::positionConstrained
    (const Vector3& position, const Atom* atom)
{
    assert(atom != 0);
    Real radius = atom->getRadius();
    
    return 
        !checkCollisionAtoms(position, radius, atom) &&
        !Global::getTerrain()->checkCollision(position, radius) &&
        atom->checkConstraintBonds(position);
}

