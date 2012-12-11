#ifndef TRANSFORMBOUND_HPP
#define TRANSFORMBOUND_HPP

#include "Transform.hpp"

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
};

#endif

