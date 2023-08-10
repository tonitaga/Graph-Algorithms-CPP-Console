#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H

#include <string_view>

#include "file_manager.h"

namespace ng {
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
        explicit Graph(std::string_view file_path);

        void LoadGraphFromFile(std::basic_string_view<char> file_path);
        void ExportGraphToDot(std::basic_string_view<char> file_path) noexcept;

        bool isEmpty() const noexcept;
        size_type getVertexesCount() const noexcept;
        size_type getEdgesCount() const noexcept { return edges_.size(); }
        GraphType getGraphType() const noexcept { return graph_type_; }
        std::vector<edge_type> getEdges() const noexcept { return edges_; }
        Matrix<value_type> getAdjacencyMatrix() const noexcept { return adjacency_matrix_; }

        const_reference operator()(size_type from, size_type to) const;

    private:
        Matrix<value_type> adjacency_matrix_;
        std::vector<edge_type> edges_;
        value_type default_value_ {};
        GraphType graph_type_ = GraphType::kEmptyGraph;

    private:
        void CountEdgesAndGraphType();
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const Graph<T> &graph);
}

#include "graph.tpp"

#endif //GRAPHALGORITHMS_GRAPH_H
