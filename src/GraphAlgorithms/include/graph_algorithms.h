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

    template<typename T, typename Container = std::stack<T>>
    std::vector<T> GraphAlgorithms::FirstSearch(const Graph<T> &graph, std::size_t start_vertex) {
        if (graph.isEmpty() or start_vertex > graph.getVertexesCount())
            return {};

        constexpr bool is_dfs = std::is_same_v<Container, std::stack<T>>;
        const std::size_t vertexes_count = graph.getVertexesCount();

        std::vector<T> enter_order;
        std::vector<std::size_t> visited(vertexes_count);
        Container c;

        --start_vertex;
        visited[start_vertex] = true;
        c.push(start_vertex);
        enter_order.emplace_back(start_vertex + 1);

        while (!c.empty()) {
            std::size_t from = 0;
            if constexpr (is_dfs) {
                from = c.top();
            } else {
                from = c.front();
                c.pop();
            }

            bool is_found = false;

            for (std::size_t to = 0; to != vertexes_count; ++to) {
                if (!visited[to] and graph(from, to) != 0) {
                    if (is_dfs)
                        from = to;
                    is_found = true;
                    visited[to] = true;
                    c.push(to);
                    enter_order.emplace_back(to + 1);
                }
            }

            if (is_dfs and !is_found)
                c.pop();
        }

        return enter_order;
    }

    template<typename T>
    std::vector<T> GraphAlgorithms::DepthFirstSearch(const Graph<T> &graph, std::size_t start_vertex) {
        return FirstSearch<T>(graph, start_vertex);
    }

    template<typename T>
    std::vector<T> GraphAlgorithms::BreadthFirstSearch(const Graph<T> &graph, std::size_t start_vertex) {
        return FirstSearch<T, std::queue<T>>(graph, start_vertex);
    }
}

#endif //GRAPHALGORITHMS_GRAPH_ALGORITHMS_H
