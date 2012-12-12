#ifndef TRANSFORMBOUND_HPP
#define TRANSFORMBOUND_HPP

#include <Ogre.h>
#include "Transforms.hpp"

/**
 * Class TransformBound
 * Représente la transformation de type bound
 */
class TransformBound : public Transform
{
    public:

        /**
         * Contruit la transformation bound
         * à partir du graphe local
         */
        TransformBound(Graph* graph);

        /**
         * Implémente doTransform
         */
        virtual bool doTransformStep();
        
        /**
         * Renvoi true si l'atome donné
         * est un atome d'action pour cette
         * transformation
         */
        static bool isActionAtom(const Atom* atom);

    private:

        /**
         * Longueur des liaisons créées
         */
        static const Ogre::Real BOND_LENGTH = 250;
};

#endif

