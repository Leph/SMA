#ifndef ATOM_HPP
#define ATOM_HPP

#include <vector>
#include <Ogre.h>
#include "Bond.hpp"

/**
 * Atom
 * Classe de base pour toutes les particules
 * classe Abstraite
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
        virtual ~Atom();

        /**
         * Renvoi le rayon
         */
        Ogre::Real getRadius() const;

        /**
         * Renvoi la position
         */
        const Ogre::Vector3& getPosition() const;

        /**
         * Renvoi true si l'atome représente 
         * l'atome spécifié
         */
        virtual bool isRepresent(const Atom* atom) const = 0;

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
         * de liaison. La liaison doit avoir
         * été définie.
         * Il ne peut pas y avoir deux liaisons
         * vers le même atome
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

        /**
         * renvoi true si cet atome est
         * lié à un autre atome donné
         */
        bool isBoundTo(Atom* atom);

        /**
         * Transfert les liaisons de cet atome
         * vers l'atome spécifé.
         * Après, cet atome n'a plus de liasons
         */
        void transfertBonds(Atom* atom);

        /**
         * Renvoi true si l'atome est de class T
         */
        template <class T>
        bool isType() const {
            return dynamic_cast<T*>(const_cast<Atom*>(this)) != 0;
        }

        /**
         * Renvoi l'index de l'atome dans le tableau 
         * de l'AtomManager
         */
        size_t getIndex() const;

        /**
         * Défini l'index de l'atome
         * Appelé uniquement par AtomManager
         */
        void setIndex(size_t index);

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
         * Indice de l'atome dans le conteneur
         * de l'AtomManager
         */
        size_t _index;

        /**
         * Créer et initialise le Node Ogre pour
         * la représentation graphique
         * Spécifie la couleur et la forme
         * de la représentation
         */
        void initNode(
            Ogre::ManualObject* manual, 
            const Ogre::ColourValue& colour);

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

