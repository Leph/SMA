#ifndef POSITIONRESOLVER_HPP
#define POSITIONRESOLVER_HPP

#include <Ogre.h>
#include "Atom.hpp"

/**
 * PositionResolver
 * Cette classe permet de gerer les contraintes
 * de position des atoms. Résolution des collisions
 * et placement dans l'espace
 */
class PositionResolver
{
    public:

        /**
         * Initialise le resolver
         */
        PositionResolver();

        /**
         * Détruit le résolver
         */
        ~PositionResolver();

        /**
         * Renvoi la liste de tous les atomes
         * qui intersectent la sphère spécifiée
         * Si exclude est défini, l'atome ne sera pas présent
         * dans la liste
         * Attention, la liste renvoyée changera à la
         * prochaine requète
         */
        std::list<Atom*>& findAtoms(
            const Ogre::Vector3& center, 
            Ogre::Real radius, const Atom* exclude = 0);

        /**
         * Renvoi true si un atome intersecte la sphère
         * spécifiée
         * Si exclude est défini, l'atome sera ignoré
         */
        bool checkCollisionAtoms(const Ogre::Vector3& center, 
            Ogre::Real radius, const Atom* exclude = 0);

        /**
         * Renvoi true si la position pour l'atome spécifié
         * vérifie les contraintes de position spatiale
         * Utilisé par le resolver
         */
        bool positionConstrained
            (const Ogre::Vector3& position, const Atom* atom);

        /**
         * Renvoi la nouvelle position de l'atome
         * donné et se déplaçant du vecteur
         * motion en tenant compte de toutes les 
         * collisions avec les autres atomes
         */
        Ogre::Vector3 resolve
            (const Atom* atom, const Ogre::Vector3& motion);

    private:

        /**
         * Requète Ogre pour récupérer tous les
         * entités d'une régions de l'espace
         */
        Ogre::AxisAlignedBoxSceneQuery* _query;
    
        /**
         * Liste d'atomes stokant le résultat
         * des requètes de scenes
         */
        std::list<Atom*> _resultQuery;
};

#endif

