#ifndef ATOM_HPP
#define ATOM_HPP

#include <Ogre.h>

/**
 * Classe de base pour toutes les particules
 */
class Atom
{
    public:

        /**
         * Construit et initialise l'atome
         */
        Atom(Ogre::Real radius, Ogre::Vector3 position);

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
         * Tests des collisions
         *
         * @param dt : pas de temps
         */
        void move(Ogre::Real dt);

        /**
         * Réinitialise et calcul les forces
         * appliquée à l'atome
         * Donne le vecteur de déplacement
         */
        void computeMove();

    protected:

        /**
         * Le rayon de l'atome
         */
        Ogre::Real _radius;

        /**
         * Sa position
         */
        Ogre::Vector3 _position;

        /**
         * La somme des forces instantannées qui
         * lui sont appliqué (ex : gravité, mouvement brownien)
         */
        Ogre::Vector3 _force;

        /**
         * Le noeud Ogre auquel est rataché la représentation
         * graphique de l'atome
         */
        Ogre::SceneNode* _node;

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
        Ogre::Vector3 applyBrownian();
};

#endif

