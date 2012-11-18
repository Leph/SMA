#include <cstdlib>
#include <assert.h>
#include <Plugins/OctreeSceneManager/OgreOctreeSceneManager.h>

#include "AtomManager.hpp"
#include "Global.hpp"

using Ogre::Vector3;
using Ogre::Real;
using Ogre::AxisAlignedBox;
using Ogre::AxisAlignedBoxSceneQuery;
using Ogre::SceneQueryResult;
using Ogre::Any;

AtomManager::AtomManager() :
    _atoms(),
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

AtomManager::~AtomManager()
{
    //Désallocation des atomes dans le conteneur
    for (size_t i=0;i<_atoms.size();i++) {
        if (_atoms[i] != 0) {
            delete _atoms[i];
            _atoms[i] = 0;
        }
    }
    //Destruction de la requète de scene
    Global::getSceneManager()->destroyQuery(_query);
}

size_t AtomManager::getSize() const
{
    return _atoms.size();
}

Atom* AtomManager::get(size_t index) const
{
    assert(index >= 0 && index < _atoms.size());
    assert(_atoms[index] != 0);

    return _atoms[index];
}

void AtomManager::add(Atom* atom)
{
    assert(atom != 0);
    _atoms.push_back(atom);
}

void AtomManager::remove(size_t index)
{
    assert(index >= 0 && index < _atoms.size());
    assert(_atoms[index] != 0);

    delete _atoms[index];
    _atoms[index] = 0;
}

void AtomManager::shuffle()
{
    //Nettoi les cases des atomes précédemment supprimés
    size_t i = 0;
    while (i < _atoms.size()) {
        if (_atoms[i] == 0) {
            _atoms[i] = _atoms[_atoms.size()-1];
            _atoms.pop_back();
        } else {
            i++;
        }
    }

    //Mélange aléatoirement le conteneur
    for (i=_atoms.size()-1;i>=1;i--) {
        Atom* tmp;
        size_t index = rand() % i;
        tmp = _atoms[index];
        _atoms[index] = _atoms[i];
        _atoms[i] = tmp;
    }
}

std::list<Atom*>& AtomManager::findNeighbors
    (size_t index, Real radius)
{
    assert(index >= 0 && index < _atoms.size());
    assert(_atoms[index] != 0);

    //Définie la nouvelle requète
    _query->setBox(
        AxisAlignedBox(
            _atoms[index]->getPosition()-radius, 
            _atoms[index]->getPosition()+radius
    ));
    
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
            if (atom != 0 && atom != _atoms[index]) {
                _resultQuery.push_front(atom);
            }
        }
        result.movables.pop_front();
    }

    return _resultQuery;
}

bool AtomManager::checkCollisions
    (Vector3 center, Real radius, const Atom* exclude)
{
    //Définie la nouvelle requète
    _query->setBox(
        AxisAlignedBox(center-radius, center+radius));
    
    //Requète (Octree)
    SceneQueryResult& result = _query->execute();

    //Récupération et filtrage des résultats
    while (!result.movables.empty()) {
        Any any = result.movables.front()
            ->getUserObjectBindings().getUserAny();
        if (!any.isEmpty()) {
            Atom* atom = Ogre::any_cast<Atom*>(any);
            if (atom != 0 && atom != exclude) {
                Real distance = atom->getPosition()
                    .squaredDistance(center)
                    - (atom->getRadius()+radius)
                    *(atom->getRadius()+radius);
                if (distance <= 0) {
                    return true;
                }
            }
        }
        result.movables.pop_front();
    }

    return false;
}

