#ifndef TRANSFORMUNBOUND_HPP
#define TRANSFORMUNBOUND_HPP

#include <Ogre.h>
#include "Transforms.hpp"

/**
 * Class TransformUnbound
 * Représente la transformation de type unbound
 */
class TransformUnbound : public Transform
{
    public:

        /**
         * Contruit la transformation unbound
         * à partir du graphe local
         */
        TransformUnbound(Graph* graph);

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

