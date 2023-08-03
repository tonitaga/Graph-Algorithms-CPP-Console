#ifndef GRAPHALGORITHMS_GRAPH_ALGORITHMS_H
#define GRAPHALGORITHMS_GRAPH_ALGORITHMS_H

#include <limits>

#include "graph.h"

namespace ng {
    class GraphAlgorithms final {
    public:
        template<typename T>
        static std::vector<T> BreadthFirstSearch(const Graph<T> &g, std::size_t start_vertex);

        template<typename T>
        static std::vector<T> DepthFirstSearch(const Graph<T> &g, std::size_t start_vertex);

        template<typename T>
        static T GetShortestPathBetweenVertices(const Graph<T> &g, std::size_t start_vertex, std::size_t finish_vertex);

        template<typename T>
        static Matrix<T> GetShortestPathsBetweenAllVertices(const Graph<T> &graph);

    private:
        template<typename T, typename Container>
        static std::vector<T> FirstSearch(const Graph<T> &g, std::size_t start_vertex);
    };
}

#include "graph_algorithms.tpp"

#endif //GRAPHALGORITHMS_GRAPH_ALGORITHMS_H
