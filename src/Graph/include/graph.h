#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H

#include <string_view>

#include "matrix.h"
#include "file_manager.h"

namespace ng {
    enum class GraphType : int {
        kEmptyGraph,
        kDirectedGraph,
        kUndirectedGraph,
        kMultiGraph
    };

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
        size_type getEdgesCount() const { return edges_count_; }
        GraphType getGraphType() const { return graph_type_; }

        const_reference operator()(size_type from, size_type to) const;

    private:
        Matrix<value_type> adjacency_matrix_;
        size_type edges_count_ {};
        value_type default_value_ {};

        GraphType graph_type_ = GraphType::kEmptyGraph;

    private:
        void CountEdgesAndGraphType();
    };
}

#include "graph.tpp"

#endif //GRAPHALGORITHMS_GRAPH_H
