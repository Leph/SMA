#ifndef ATOM_HPP
#define ATOM_HPP

#include <vector>
#include <Ogre.h>
#include "Bond.hpp"

/**
 * Classe de base pour toutes les particules
 */
class Atom
{
    public:

        /**
         * Construit et initialise l'atome
         */
        Atom(Ogre::Real radius, const Ogre::Vector3& position);

        /**
         * Supprime le Node des données d'Ogre
         */
        ~Atom();

        /**
         * Renvoi le rayon
         */
        Ogre::Real getRadius() const;

        /**
         * Renvoi la position
         */
        const Ogre::Vector3& getPosition() const;

        /**
         * Déplace l'atome
         * Intégration des forces directement sur la position
         * Déplacement du node d'Ogre de la scène
         * Calcul des forces
         * Tests des collisions
         *
         * @param dt : pas de temps
         */
        void move(Ogre::Real dt);

        /**
         * Ajoute une liaison au conteneur
         * de liaison
         */
        void addBond(Bond* bond);

        /**
         * Supprime une liaison du
         * conteneur
         * Ne désalloue pas la liaison
         * (Cette méthode est appelée par
         * Bond)
         */
        void delBond(Bond* bond);

        /**
         * Renvoi true si le déplacement
         * est compatible avec les liaisons
         * de l'atome
         */
        bool checkConstraintBonds
            (const Ogre::Vector3& position) const;

    protected:

        /**
         * Le rayon de l'atome
         */
        Ogre::Real _radius;

        /**
         * Sa position actuelle
         */
        Ogre::Vector3 _position;

        /**
         * Représente la direction du mouvement brownien
         * de l'atome. 
         * Utilisé par la methode applyBrownian
         */
        Ogre::Vector3 _brownianMotion;

        /**
         * Compte le temps avant recalcul du mouvement
         * brownlien.
         * Utilisé par la methode applyBrownian
         */
        Ogre::Real _brownianCounter;

        /**
         * Le noeud Ogre auquel est rataché la représentation
         * graphique de l'atome
         */
        Ogre::SceneNode* _node;

        /**
         * Conteneur pour les liaisons
         * de l'atome
         */
        std::vector<Bond*> _bonds;

        /**
         * Créer et initialise le Node Ogre pour
         * la représentation graphique
         */
        void initNode();

        /**
         * Renvoi la force de gravitation
         * appliquée sur l'atome
         */
        Ogre::Vector3 applyGravity();

        /**
         * Renvoi le mouvement brownien
         * appliqué sur l'atome
         */
        Ogre::Vector3 applyBrownian(Ogre::Real dt);
};

#endif

