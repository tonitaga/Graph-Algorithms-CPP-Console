#include "graph.h"

#include <cassert>

void TestGraph() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix5.txt");
    assert(graph.getEdgesCount() == 55);
    assert(graph.getGraphType() == ng::GraphType::kUndirectedGraph);
    std::cout << "Graph edges count: " << graph.getEdgesCount() << std::endl;
    auto graph_edges = graph.getEdges();
    for (const auto &edge : graph_edges)
        std::cout << edge << std::endl;
}

int main() {
    TestGraph();
}