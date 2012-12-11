#include <vector>
#include <assert.h>

#include "TransformLambda.hpp"
#include "Atoms.hpp"

TransformLambda::TransformLambda(Graph& graph) :
    Transform(graph)
{
    assert(_graph.sizeVertex() > 0);
    assert(_graph.getVertex(0)->isType<Atom_Lambda>());

    //Parcours des voisins de l'atome d'action
    //lambda
    size_t sizeEdgeLambda = _graph.sizeEdge(0);
    for (size_t i=0;i<sizeEdgeLambda;i++) {
        size_t srcIndex = _graph.getEdge(0, i);
        //Si il s'agit d'un atome d'application
        //on l'enregistre
        if (_graph.getVertex(srcIndex)
            ->isType<Atom_Apply>()
        ) {
            _apply.push_back(Star(srcIndex, 0));
        }
        //Sinon on regarde si il peut s'agir d'une
        //étoile avec un atome d'association
        else {
            //Parcours des voisins de l'atome
            //On cherche les atomes d'association
            size_t sizeEdgeSrc = _graph
                .sizeEdge(srcIndex);
            size_t associationFounded = 0;
            size_t associationIndex = 0;
            for (size_t j=0;j<sizeEdgeSrc;j++) {
                size_t index = _graph.getEdge(srcIndex, j);
                if (_graph.getVertex(index)
                    ->isType<Atom_Association>()
                ) {
                    associationFounded++;
                    associationIndex = index;
                }
            }
            //Si un unique atome d'association est trouvé
            //on vérifie qu'il ne lie que deux atomes
            if (associationFounded == 1) {
                if (_graph.sizeEdge(associationIndex) == 2) {
                    size_t dstIndex = 
                        _graph.getEdge(associationIndex, 0) == 
                        srcIndex ? 
                        _graph.getEdge(associationIndex, 1) : 
                        _graph.getEdge(associationIndex, 0);
                    _src.push_back(
                        Star(srcIndex, 0, associationIndex));
                    _dst.push_back(
                        Star(dstIndex, associationIndex));
                }
            }
        }
    }

    //Pour être valide, il faut que la transformation 
    //possède au moins un atome d'application voisin
    //de lambda
    //ainsi qu'un couple d'étoiles associés
    _isValid = _apply.size() > 0 && _src.size() > 0;
    assert(_src.size() == _dst.size());

    //Initialise le parcours du graphe
    if (_isValid) {
        initTraversing();
    }
}

bool TransformLambda::doTransformStep()
{
    assert(_isValid);

    //Parcours un sommet du graphe
    size_t index = _graph.nextVertexBFS();
    if (index == -1) {
        return false;
    }

    //Test pour tous les patterns src
    std::vector<size_t> matches;
    for (size_t i=0;i<_src.size();i++) {
        matches.clear();
        //Test du pattern d'étoile
        if (matchStar(_src[i], Star(index), matches)) {
            std::cout << "Matches" << std::endl;
            //Remplace le centre de l'étoile ayant matché
            //avec le centre de l'étoile dst
            bool success = 
                replaceAtom(_dst[i].center(), index);
            //Le remplacement à réussi
            if (success) {
                std::cout << "->Replaced" << std::endl;
                break;
            }
        } 
    }

    return true;
}

