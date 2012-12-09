#ifndef BOND_HPP
#define BOND_HPP

#include <Ogre.h>

//Double header inclusion
class Atom;

class Bond
{
    public:

        /**
         * Construit et initialise la liaison
         */
        Bond(Atom* a1, Atom* a2, Ogre::Real length);

        /**
         * Supprime le Node des données d'Ogre
         */
        ~Bond();

        /**
         * Renvoi la longueur de la liaison
         */
        Ogre::Real getLength() const;

        /**
         * Renvoi l'autre bout de la liason
         * Le bout actuel étant atom
         */
        Atom* getOtherEnd(const Atom* atom) const;

        /**
         * Le bout de la liaison correspondand à src
         * est remplacé par dst
         */
        void transfertEnd(Atom* src, Atom* dst);

        /**
         * Met à jour la représentation graphique
         */
        void updateNode();

        /**
         * Renvoi true si le déplacement de l'atome 
         * spécifié est compatible avec la liaison
         */
        bool checkConstraint(const Atom* atom, 
            const Ogre::Vector3& position) const;

        /**
         * Supprime la liaison (et se supprime
         * des atomes concernés)
         */
        void remove();

    private:

        /**
         * Une extremité de la liaison
         */
        Atom* _end1;

        /**
         * L'autre extremité
         */
        Atom* _end2;

        /**
         * La distance de la liaison
         */
        Ogre::Real _length;

        /**
         * Le noeud Ogre auquel est rataché la représentation
         * graphique de la liaison
         */
        Ogre::SceneNode* _node;

        /**
         * Créer et initialise le Node Ogre pour
         * la représentation graphique
         */
        void initNode();
};

#endif

