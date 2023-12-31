#ifndef GRAPHALGORITHMS_GRAPH_TPP
#define GRAPHALGORITHMS_GRAPH_TPP

#include "graph.h"

namespace ng {

    ///
    ///   Implementation of Graph class
    ///

    template<typename T>
    Graph<T>::Graph(const Matrix<value_type> &adjacency_matrix)
        : adjacency_matrix_(adjacency_matrix) {
        CountEdgesAndGraphType();
    }

    template <typename T>
    Graph<T>::Graph(std::string_view file_path)
        : adjacency_matrix_(FileManager::ReadMatrixFromFile<T>(file_path)) {
        CountEdgesAndGraphType();
    }

    template <typename T>
    void Graph<T>::LoadGraphFromFile(std::basic_string_view<char> file_path) {
        adjacency_matrix_ = FileManager::ReadMatrixFromFile<T>(file_path);
        CountEdgesAndGraphType();
    }

    template <typename T>
    void Graph<T>::ExportGraphToDot(std::basic_string_view<char> file_path) noexcept {
        FileManager::ExportGraphToDot(edges_, graph_type_, file_path);
    }

    template <typename T>
    bool Graph<T>::isEmpty() const noexcept {
        return adjacency_matrix_.getRows() == 0;
    }

    template <typename T>
    typename Graph<T>::size_type Graph<T>::getVertexesCount() const noexcept {
        return adjacency_matrix_.getRows();
    }

    template <typename T>
    typename Graph<T>::const_reference Graph<T>::operator()(size_type from, size_type to) const {
        return adjacency_matrix_(from, to);
    }

    template <typename T>
    void Graph<T>::CountEdgesAndGraphType() {
        edges_.clear();
        graph_type_ = GraphType::kEmptyGraph;

        bool is_directed = true, is_undirected = true;
        for (size_type from = 0, size = getVertexesCount(); from != size; ++from) {
            for (size_type to = from; to != size; ++to) {
                if (from == to and adjacency_matrix_(from, to) != default_value_) {
                    edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_ and
                           adjacency_matrix_(from, to) != adjacency_matrix_(to, from)) {
                    edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                    edges_.emplace_back(to, from, adjacency_matrix_(from, to));
                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_) {
                    edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                    is_directed = false;
                } else if (adjacency_matrix_(from, to) != default_value_ or
                           adjacency_matrix_(to, from) != default_value_) {
                    if (adjacency_matrix_(from, to) != default_value_)
                        edges_.emplace_back(from, to, adjacency_matrix_(from, to));
                    else
                        edges_.emplace_back(to, from, adjacency_matrix_(from, to));
                    is_undirected = false;
                }
            }
        }

        if (edges_.empty())
            return;

        if (is_directed) graph_type_ = GraphType::kDirectedGraph;
        else if (is_undirected) graph_type_ = GraphType::kUndirectedGraph;
        else graph_type_ = GraphType::kMultiGraph;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Graph<T> &graph) {
        out << "Graph contains:\n\t";
        out << "Vertexes count: " << graph.getVertexesCount() << "\n\t";
        out << "Edges count:    " << graph.getEdgesCount() << "\n\t";
        out << "Adjacency Matrix:\n";
        out << graph.getAdjacencyMatrix();
        return out;
    }
}

#endif //GRAPHALGORITHMS_GRAPH_TPP
