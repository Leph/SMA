#ifndef STAR_HPP
#define STAR_HPP

#include <Ogre.h>

/**
 * Class Star
 *
 * Structure de donnée permet de 
 * représenter une étoile dans un graphe
 */
class Star
{
    public:

        /**
         * Initialise l'étoile
         */
        Star(size_t center, 
            size_t exclude1 = -1, size_t exclude2 = -1);

        /**
         * Accesseurs
         */
        size_t center() const;
        size_t exclude1() const;
        size_t exclude2() const;

    private:
        
        /**
         * Indice de l'atome au centre
         * de l'étoile
         */
        size_t _center;

        /**
         * Indice des atomes dans le voisinage
         * de center exclus de l'étoile
         * -1 si le champ est non utilisé
         * Le champ exclude1 doit être utilisé
         * avant exclude2
         */
        size_t _exclude1;
        size_t _exclude2;
};

#endif

