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

        /**
         * Récupère et renvoi la liste de tous les atomes 
         * dans un rayon donné autour de l'atome d'index
         * spécifié. L'atome source est exclut de la liste
         */
        std::list<Atom*>& findNeighbors
            (size_t index, Ogre::Real radius);

        /**
         * Renvoi true si un atome se trouve dans
         * la sphere donnée.
         * Si exclude est défini, l'atome n'est pas pris
         * en compte
         */
        bool checkCollisions(Ogre::Vector3 center, 
            Ogre::Real radius, const Atom* exclude = 0);

    private:

        /**
         * Conteneur standard (vector) des
         * atomes
         */
        std::vector<Atom*> _atoms;

        /**
         * Requète Ogre pour récupérer tous les
         * entités d'une régions de l'espace
         */
        Ogre::SphereSceneQuery* _query;
    
        /**
         * Liste d'atomes stokant le résultat
         * des requètes de scenes
         */
        std::list<Atom*> _resultQuery;
};

#endif

