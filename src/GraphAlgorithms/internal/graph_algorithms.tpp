#ifndef GRAPHALGORITHMS_GRAPH_ALGORITHMS_TPP
#define GRAPHALGORITHMS_GRAPH_ALGORITHMS_TPP

#include "graph_algorithms.h"

#include <stack>
#include <queue>
#include <set>

namespace ng {
    template<typename T, typename Container = std::stack<T>>
    std::vector<T> GraphAlgorithms::FirstSearch(const Graph<T> &graph, std::size_t start_vertex) {
        if (graph.isEmpty() or start_vertex > graph.getVertexesCount())
            return {};

        constexpr bool is_dfs = std::is_same_v<Container, std::stack<T>>;
        const std::size_t kVertexesCount = graph.getVertexesCount();

        std::vector<T> enter_order;
        std::vector<std::size_t> visited(kVertexesCount);
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

            for (std::size_t to = 0; to != kVertexesCount; ++to) {
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

    template<typename T>
    T GraphAlgorithms::GetShortestPathBetweenVertices(const Graph<T> &graph, std::size_t start_vertex,
                                                      std::size_t finish_vertex) {
        const std::size_t kVertexesCount = graph.getVertexesCount();
        if (graph.isEmpty() or start_vertex > kVertexesCount or finish_vertex > kVertexesCount)
            return kInf<T>;


        std::vector<T> distance(kVertexesCount, kInf<T>);

        --start_vertex, --finish_vertex;
        distance[start_vertex] = 0;

        std::set<std::pair<T, std::size_t>> q;
        q.insert({distance[start_vertex], start_vertex});

        while (!q.empty()) {
            auto from = q.begin()->second;
            q.erase(q.begin());

            for (std::size_t to = 0; to != kVertexesCount; ++to) {
                if (graph(from, to) != 0 and distance[to] > distance[from] + graph(from, to)) {
                    q.erase({distance[to], to});
                    distance[to] = distance[from] + graph(from, to);
                    q.insert({distance[to], to});
                }
            }
        }

        return distance[finish_vertex];
    }
}

#endif //GRAPHALGORITHMS_GRAPH_ALGORITHMS_TPP
