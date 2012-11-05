#ifndef ATOMMANAGER_HPP
#define ATOMMANAGER_HPP

#include <vector>
#include <Ogre.h>
#include "Atom.hpp"

/**
 * Classe conteneur et gérant tous les atomes
 * de la simulation
 * L'instance est globale
 */
class AtomManager
{
    public:

        /**
         * Créer et initialise le conteneur
         */
        AtomManager();

        /**
         * Détruit tous les atomes
         */
        ~AtomManager();

        /**
         * Renvoi le nombre d'atomes dans le conteneur
         */
        size_t getSize() const;

        /**
         * Renvoi un atome par son index dans 
         * le conteneur
         */
        Atom* get(size_t index) const;

        /**
         * Ajoute un nouvel atome au conteneur
         * L'atome doit être alloué dynamiquement (new)
         */
        void add(Atom* atom);

        /**
         * Supprimer du conteneur par son index
         * Désallocation (delete)
         * Supprime l'atome des données d'Ogre
         */
        void remove(size_t index);

        /**
         * Mélange les atomes avec 
         * une permutation aléatoire
         * Nettoi le conteneur des atomes supprimés
         * Complexité linéaire
         */
        void shuffle();

    private:

        /**
         * Conteneur standard (vector) des
         * atomes
         */
        std::vector<Atom*> _atoms;
};

#endif

