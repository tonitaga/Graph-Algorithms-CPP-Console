#ifndef GRAPHALGORITHMS_GRAPH_ALGORITHMS_TPP
#define GRAPHALGORITHMS_GRAPH_ALGORITHMS_TPP

#include "graph_algorithms.h"
#include "graph_help.h"

#include "stack.h"
#include "queue.h"

#include <set>

namespace ng {
    template<typename T, typename Container = Stack<T>>
    std::vector<std::size_t> GraphAlgorithms::FirstSearch(const Graph<T> &graph, std::size_t start_vertex) {
        if (graph.isEmpty() or start_vertex > graph.getVertexesCount())
            return {};

        constexpr bool is_dfs = std::is_same_v<Container, Stack<T>>;
        const std::size_t kVertexesCount = graph.getVertexesCount();

        std::vector<std::size_t> enter_order;
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
    std::vector<std::size_t> GraphAlgorithms::DepthFirstSearch(const Graph<T> &graph, std::size_t start_vertex) {
        return FirstSearch<T>(graph, start_vertex);
    }

    template<typename T>
    std::vector<std::size_t> GraphAlgorithms::BreadthFirstSearch(const Graph<T> &graph, std::size_t start_vertex) {
        return FirstSearch<T, Queue<T>>(graph, start_vertex);
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

    template<typename T>
    Matrix<T> GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph<T> &graph) {
        if (graph.isEmpty())
            return {};

        const std::size_t kVertexesCount = graph.getVertexesCount();

        Matrix<T> distances_matrix(kVertexesCount, kInf<T>);

        for (std::size_t row = 0; row != kVertexesCount; ++row)
            for (std::size_t col = 0; col != kVertexesCount; ++col) {
                distances_matrix(row, col) = graph(row, col) == 0 ? kInf<T> : graph(row, col);
                if (row == col)
                    distances_matrix(row, col) = 0;
            }

        for (std::size_t v = 0; v != kVertexesCount; ++v)
            for (std::size_t row = 0; row != kVertexesCount; ++row)
                for (std::size_t col = 0; col != kVertexesCount; ++col) {
                    auto weight = distances_matrix(row, v) + distances_matrix(v, col);
                    if (distances_matrix(row, v) != kInf<T> and distances_matrix(v, col) != kInf<T> and
                        distances_matrix(row, col) > weight) {
                        distances_matrix(row, col) = weight;
                    }
                }

        return distances_matrix;
    }

    template<typename T>
    Matrix<T> GraphAlgorithms::GetLeastSpanningTree(const Graph<T> &graph) {
        if (graph.isEmpty())
            return {};

        const std::size_t kVertexesCount = graph.getVertexesCount();

        Matrix<T> spanning_tree(kVertexesCount, kInf<T>);
        std::set<std::size_t> visited, unvisited;
        std::vector<GraphEdge<T>> tree_edges;

        for (std::size_t v = 0; v != kVertexesCount; ++v)
            unvisited.insert(v);

        const auto start_vertex = kVertexesCount / 2;
        visited.insert(start_vertex);
        unvisited.erase(start_vertex);

        while (!unvisited.empty()) {
            GraphEdge<T> edge = GraphEdge<T>::UndetectedEdge();

            for (const auto &from : visited) {
                for (std::size_t to = 0; to != kVertexesCount; ++to) {
                    bool is_unvisited_vertex = unvisited.find(to) != unvisited.end();
                    bool edge_is_exists = graph(from, to) != 0 or graph(to, from) != 0;

                    if (edge_is_exists and is_unvisited_vertex) {
                        T existed_weight = graph(from, to) == 0 ? graph(to, from) : graph(from, to);
                        bool edge_is_shorter = edge.weight > existed_weight;

                        if (edge_is_shorter)
                            edge = {from, to, existed_weight};
                    }
                }
            }

            if (edge.weight != kInf<T>) {
                tree_edges.emplace_back(edge);
                visited.insert(edge.to);
                unvisited.erase(edge.to);
            } else
                break;
        }

        for (const auto &edge : tree_edges) {
            spanning_tree(edge.from, edge.to) = edge.weight;
            spanning_tree(edge.to, edge.from) = edge.weight;
        }

        return spanning_tree;
    }

    template<typename T>
    TsmProblem<T> GraphAlgorithms::SolveSalesmansProblem(const Graph<T> &graph) {
        AntColony<T> ant_colony(graph);
        return ant_colony.SolveSalesmansProblem();
    }
}

#endif //GRAPHALGORITHMS_GRAPH_ALGORITHMS_TPP
