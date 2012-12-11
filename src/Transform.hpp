#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include <Ogre.h>
#include "Graph.hpp"
#include "Star.hpp"

/**
 * Class Transform
 *
 * Représente une transformation
 * des atomes sur un Graph
 */
class Transform
{
    public:

        /**
         * Initialise la transformation à partir
         * du graph local
         */
        Transform(Graph& graph);

        /**
         * Renvoi true si la transformation
         * est valide
         */
        bool isValid() const;

        /**
         * Effectue une étape de la transformation
         * (traite un sommet du graphe)
         * Renvoi true si la transformation n'est
         * pas fini
         */
        virtual bool doTransformStep() = 0;

    protected:

        /**
         * Vaut true si la transformation
         * est valide
         */
        bool _isValid;

        /**
         * Le graph sur lequel porte 
         * la transformation
         */
        Graph& _graph;

        /**
         * Liste des atomes d'applications
         * Exclude1 contient l'atome
         * d'action
         */
        std::vector<Star> _apply;

        /**
         * Liste des atomes initiaux
         * à rechercher.
         * Exclude 1 contient l'atome d'action
         * Exclude 2 contient l'atome d'association
         * si besoin
         */
        std::vector<Star> _src;

        /**
         * Liste des atomes à remplacer
         * (chaque indice correspond à un atome
         * src)
         * Exclude1 contient l'atome d'association
         */
        std::vector<Star> _dst;

        /**
         * Parcours le graphe et construit la 
         * transformation autour de l'atome d'action
         * pour une étoile associée à une autre étoile
         */
        void buildTranformDoubleAssociation();

        /**
         * Not yet implemented
         */
        void buildTransformSimpleAssociation();

        /**
         * Initialise le parcours du graphe
         * a partir des atomes d'application
         */
        void initTraversing();

        /**
         * Renvoi true si l'étoile src représente 
         * l'étoile dst, false sinon
         * Si il y a correspondance, les indices
         * (dans le graph) des atomes voisins de dst 
         * ayant correspondus sont insérés dans matches
         */
        bool matchStar(const Star& src, const Star& dst, 
            std::vector<size_t>& matches) const;

        /**
         * Remplace l'atome dst par l'atome src
         * Les atomes sont spécifié par leur indice 
         * dans le graph
         * Renvoi true si l'opération réussie
         */
        bool replaceAtom(size_t src, size_t dst) const;
};

#endif

