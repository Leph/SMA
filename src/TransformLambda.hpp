#ifndef TRANSFORMLAMBDA_HPP
#define TRANSFORMLAMBDA_HPP

#include "Transform.hpp"

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
        TransformLambda(Graph& graph);

        /**
         * Implémente doTransform
         */
        virtual bool doTransformStep();
};

#endif

