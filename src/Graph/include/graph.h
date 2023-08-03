#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H

#include <string_view>

#include "matrix.h"
#include "graph_edge.h"

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
        using edge_type = GraphEdge<T>;

    public:
        Graph() noexcept = default;
        explicit Graph(const Matrix<value_type> &adjacency_matrix);

        bool isEmpty() const noexcept;
        size_type getVertexesCount() const noexcept;
        size_type getEdgesCount() const noexcept { return edges_count_; }
        GraphType getGraphType() const noexcept { return graph_type_; }
        std::vector<edge_type> getEdges() const noexcept { return edges_; }

        const_reference operator()(size_type from, size_type to) const;

    private:
        Matrix<value_type> adjacency_matrix_;
        size_type edges_count_ {};
        value_type default_value_ {};
        GraphType graph_type_ = GraphType::kEmptyGraph;
        std::vector<edge_type> edges_;

    private:
        void CountEdgesAndGraphType();
    };
}

#include "graph.tpp"

#endif //GRAPHALGORITHMS_GRAPH_H
