#ifndef TRANSFORMLAMBDA_HPP
#define TRANSFORMLAMBDA_HPP

#include "Transforms.hpp"

/**
 * Class TransformLambda
 * Représente la transformation de type lambda
 */
class TransformLambda : public Transform
{
    public:

        /**
         * Contruit la transformation lambda
         * à partir du graphe local
         */
        TransformLambda(Graph* graph);

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
};

#endif

