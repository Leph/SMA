#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <Ogre.h>
#include "Atom.hpp"

/**
 * Représente un graphe local
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
};

#endif

