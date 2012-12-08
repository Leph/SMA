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
    std::cout << "Begin transfom construct" << std::endl;
    size_t sizeEdgeLambda = _graph.sizeEdge(0);
    for (size_t i=0;i<sizeEdgeLambda;i++) {
        size_t srcIndex = _graph.getEdge(0, i);
        //Si il s'agit d'un atome d'application
        //on l'enregistre
        if (_graph.getVertex(srcIndex)
            ->isType<Atom_Apply>()
        ) {
            std::cout << "- Apply found " << srcIndex 
                << std::endl;
            std::cout << "  Star apply " << srcIndex << " " 
                << 0 << std::endl;
            _apply.push_back(Star(srcIndex, 0));
        }
        //Sinon on regarde si il peut s'agir d'une
        //étoile avec un atome d'association
        else {
            std::cout << "- Src found " << srcIndex 
                << std::endl;
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
                    std::cout << "-- Association found " 
                        << index << std::endl;
                    associationFounded++;
                    associationIndex = index;
                }
            }
            //Si un unique atome d'association est trouvé
            //on vérifie qu'il ne lie que deux atomes
            if (associationFounded == 1) {
                std::cout << "- One Association found " 
                    << associationIndex << std::endl;
                if (_graph.sizeEdge(associationIndex) == 2) {
                    std::cout << "- One Association good found " 
                        << associationIndex << std::endl;
                    size_t dstIndex = 
                        _graph.getEdge(associationIndex, 0) == 
                        srcIndex ? 
                        _graph.getEdge(associationIndex, 1) : 
                        _graph.getEdge(associationIndex, 0);
                    std::cout << "  Star src " << srcIndex 
                        << " " << 0 << " " 
                        << associationIndex << std::endl;
                    std::cout << "  Star dst " << dstIndex 
                        << " " << associationIndex << std::endl;
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
    std::cout << "Size " << _apply.size() << " " << _src.size() 
        << " " << _dst.size() << std::endl;
    _isValid = _apply.size() > 0 && _src.size() > 0;
    assert(_src.size() == _dst.size());
    std::cout << "End transform construct" << std::endl;

    //Initialise le parcours du graphe
    initTraversing();
}

bool TransformLambda::doTransformStep()
{
    size_t index = _graph.nextVertexBFS();
    std::cout << "BFS " << index << std::endl;
    if (index == -1) {
        return false;
    }

    for (size_t i=0;i<_src.size();i++) {
        if (matchStar(_src[i], Star(index))) {
            std::cout << "Equal !" << std::endl;
        }
    }

    return true;
}

