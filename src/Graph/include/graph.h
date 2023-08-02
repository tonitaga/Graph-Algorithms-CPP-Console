#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H

#include <string_view>

#include "matrix.h"
#include "file_manager.h"

namespace ng {
    template <typename T>
    class Graph final {
        static_assert(std::is_fundamental<T>::value, "Template parameter T must be fundamental");
    public:
        using size_type = std::size_t;
        using value_type = T;
        using const_reference = const T &;

    public:
        Graph() noexcept = default;
        explicit Graph(const Matrix<value_type> &adjacency_matrix);
        explicit Graph(std::string_view path);

        bool isEmpty() const noexcept;
        size_type getVertexesCount() const noexcept;
        size_type getEdgesCount() const;

        const_reference operator()(size_type from, size_type to) const;

    private:
        Matrix<value_type> adjacency_matrix_;
        size_type edges_count_ {};
        value_type default_value_ {};

    private:
        size_type CountEdges() const;
    };


    ///
    ///   Implementation of Graph class
    ///


    template<typename T>
    Graph<T>::Graph(const Matrix<value_type> &adjacency_matrix)
        : adjacency_matrix_(adjacency_matrix)
    {
        edges_count_ = CountEdges();
    }

    template<typename T>
    Graph<T>::Graph(std::string_view path)
        : adjacency_matrix_(FileManager::ReadMatrixFromFile<value_type>(path))
    {
        edges_count_ = CountEdges();
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
    typename Graph<T>::size_type Graph<T>::getEdgesCount() const {
        return edges_count_;
    }

    template <typename T>
    typename Graph<T>::const_reference Graph<T>::operator()(size_type from, size_type to) const {
        return adjacency_matrix_(from, to);
    }

    template <typename T>
    typename Graph<T>::size_type Graph<T>::CountEdges() const {
        size_type edges_count {};

        for (size_type from = 0, size = getVertexesCount(); from != size; ++from) {
            for (size_type to = from; to != size; ++to) {
                if (from == to and adjacency_matrix_(from, to) != default_value_) {
                    ++edges_count;
                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_ and
                           adjacency_matrix_(from, to) != adjacency_matrix_(to, from)) {
                    edges_count += 2;
                } else if (adjacency_matrix_(from, to) != default_value_ and
                           adjacency_matrix_(to, from) != default_value_) {
                    ++edges_count;
                } else if (adjacency_matrix_(from, to) != default_value_ or
                           adjacency_matrix_(to, from) != default_value_) {
                    ++edges_count;
                }
            }
        }

        return edges_count;
    }
}

#endif //GRAPHALGORITHMS_GRAPH_H
