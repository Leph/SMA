#include <cstdlib>
#include <assert.h>

#include "AtomManager.hpp"
#include "Global.hpp"
#include "Bond.hpp"

using Ogre::Vector3;
using Ogre::Real;

AtomManager::AtomManager() :
    _atoms()
{
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
}

size_t AtomManager::getSize() const
{
    return _atoms.size();
}

Atom* AtomManager::get(size_t index) const
{
    assert(index >= 0 && index < _atoms.size());
    assert(_atoms[index] != 0);
    assert(_atoms[index]->getIndex() == index);

    return _atoms[index];
}

void AtomManager::add(Atom* atom)
{
    assert(atom != 0);
    atom->setIndex(_atoms.size());
    _atoms.push_back(atom);
}

void AtomManager::remove(size_t index)
{
    assert(index >= 0 && index < _atoms.size());
    assert(_atoms[index] != 0);
    assert(_atoms[index]->getIndex() == index);

    delete _atoms[index];
    _atoms[index] = 0;
}
        
void AtomManager::replace(size_t index, Atom* atom)
{
    assert(index >= 0 && index < _atoms.size());
    assert(_atoms[index] != 0);
    assert(_atoms[index]->getIndex() == index);

    delete _atoms[index];
    atom->setIndex(index);
    _atoms[index] = atom;
}

void AtomManager::shuffle()
{
    //Nettoi les cases des atomes précédemment supprimés
    size_t i = 0;
    while (i < _atoms.size()) {
        if (_atoms[i] == 0) {
            _atoms[i] = _atoms[_atoms.size()-1];
            _atoms[i]->setIndex(i);
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
        _atoms[index]->setIndex(index);
        _atoms[i] = tmp;
        _atoms[i]->setIndex(i);
    }
}

void AtomManager::createBond
    (Atom* a1, Atom* a2, Real length)
{
    assert(a1 != 0 && a2 != 0);
    assert(length > 0);

    //Donne aux deux atomes la liaison
    Bond* bond = new Bond(a1, a2, length);
    a1->addBond(bond);
    a2->addBond(bond);
}

