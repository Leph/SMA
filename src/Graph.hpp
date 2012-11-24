#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <Ogre.h>
#include "Atom.hpp"

/**
 * Représente un graphe local (non orienté)
 * utilisé lors des transformations
 * (réécriture d'étoile)
 */
class Graph
{
    public:

        /**
         * Construit et initialise le graphe
         */
        Graph();

        /**
         * Déssaloue le graph
         */
        ~Graph();

        /**
         * Reconstruit le graphe local
         * centré sur l'atome spécifié
         * Le graphe précédent est détruit
         */
        void build(Atom* atom);

        /**
         * Vide les structures de données du graph
         * Stoppe la représentation graphique
         */
        void clear();

    private:

        /**
         * Conteneur des atomes : sommets du 
         * graphe.
         * Le premier élément est l'atome
         * d'action de la transformation
         */
        std::vector<Atom*> _vertices;

        /**
         * Les arrêtes du graphe. _edges[i] 
         * correspond au ième sommet (_vertices[i])
         * Chaque ligne contient la liste des sommmets
         * successeurs
         */
        std::vector< std::vector<size_t> > _edges;

        /**
         * Le noeud Ogre auquel est ratachée la représentation
         * graphique du graph
         */
        Ogre::SceneNode* _node;

        /**
         * Distance de voisinage utilisée pour la
         * construction de graphes locaux
         * Le graphe local inclura tous les atomes
         * dans la sphère définie
         */
        static const Ogre::Real DISTANCE_NEIGHBOURHOOD = 500;

        /**
         * Distance de seuil utilisée pour la construction
         * des graphes locaux
         * Si la distance entre deux atomes est inférieure
         * à cette distance, une arrête ets créée
         */
        static const Ogre::Real DISTANCE_EDGE = 1000;

        /**
         * Ajoute le sommet spécifié
         * Renvoi son index dans le conteneur interne
         */
        size_t addVertex(Atom* atom);

        /**
         * Ajoute un lien entre les deux sommets spécifiés
         * par leur indice interne
         */
        void addEdge(size_t index1, size_t index2);

        /**
         * Créer et initialise le Node Ogre pour
         * la représentation graphique
         */
        void initNode();
};

#endif

