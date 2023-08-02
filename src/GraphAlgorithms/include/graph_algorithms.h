#ifndef GRAPHALGORITHMS_GRAPH_ALGORITHMS_H
#define GRAPHALGORITHMS_GRAPH_ALGORITHMS_H

#include "graph.h"

#include <stack>
#include <queue>

namespace ng {
    class GraphAlgorithms final {
    public:
        template<typename T>
        static std::vector<T> BreadthFirstSearch(const Graph<T> &graph, std::size_t start_vertex);

        template<typename T>
        static std::vector<T> DepthFirstSearch(const Graph<T> &graph, std::size_t start_vertex);

    private:
        template<typename T, typename Container>
        static std::vector<T> FirstSearch(const Graph<T> &graph, std::size_t start_vertex);
    };
}

#include "graph_algorithms.tpp"

#endif //GRAPHALGORITHMS_GRAPH_ALGORITHMS_H
