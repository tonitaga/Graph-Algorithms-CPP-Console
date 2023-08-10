#ifndef GRAPHALGORITHMS_GRAPH_HELP_H
#define GRAPHALGORITHMS_GRAPH_HELP_H

#include <cctype>
#include <type_traits>

namespace ng {
    enum class GraphType : int {
        kEmptyGraph,
        kDirectedGraph,
        kUndirectedGraph,
        kMultiGraph
    };

    template <typename T>
    struct GraphEdge {
        static_assert(std::is_fundamental<T>::value, "Template parameter T must be fundamental");

        std::size_t from {}, to {};
        T weight {};

        GraphEdge() = default;
        GraphEdge(std::size_t from, std::size_t to, T weight)
            : from(from), to(to), weight(weight) {}

        static GraphEdge UndetectedEdge() {
            return GraphEdge(kInf<std::size_t>, kInf<std::size_t>, kInf<T>);
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, const GraphEdge<T> &edge) {
        out << "Edge: { from: " << edge.from << ", to: " << edge.to << ", weight: " << edge.weight << " }";
        return out;
    }
}

#endif //GRAPHALGORITHMS_GRAPH_HELP_H
