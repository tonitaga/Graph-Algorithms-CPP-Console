#ifndef GRAPHALGORITHMS_GRAPH_TPP
#define GRAPHALGORITHMS_GRAPH_TPP

#include "graph.h"
#include "file_manager.h"

namespace ng {
    ///
    ///   Implementation of Graph class
    ///
    template<typename T>
    Graph<T>::Graph(const Matrix<value_type> &adjacency_matrix)
        : adjacency_matrix_(adjacency_matrix)
    {
        CountEdgesAndGraphType();
    }

    template<typename T>
    Graph<T>::Graph(std::string_view path)
        : adjacency_matrix_(FileManager::ReadMatrixFromFile<value_type>(path))
    {
        CountEdgesAndGraphType();
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
        bool is_directed = true, is_undirected = true;
        for (size_type from = 0, size = getVertexesCount(); from != size; ++from) {
            for (size_type to = from; to != size; ++to) {
                if (from == to and adjacency_matrix_(from, to) != default_value_) {
                    ++edges_count_;
                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_ and
                           adjacency_matrix_(from, to) != adjacency_matrix_(to, from)) {
                    edges_count_ += 2;
                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_) {
                    ++edges_count_;
                    is_directed = false;
                } else if (adjacency_matrix_(from, to) != default_value_ or
                           adjacency_matrix_(to, from) != default_value_) {
                    ++edges_count_;
                    is_undirected = false;
                }
            }
        }

        if (edges_count_ == 0)
            return;

        if (is_directed) graph_type_ = GraphType::kDirectedGraph;
        else if (is_undirected) graph_type_ = GraphType::kUndirectedGraph;
        else graph_type_ = GraphType::kMultiGraph;
    }
}

#endif //GRAPHALGORITHMS_GRAPH_TPP
