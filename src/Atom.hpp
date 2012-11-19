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

