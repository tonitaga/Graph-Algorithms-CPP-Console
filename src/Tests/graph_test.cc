#include "graph.h"

#include <cassert>

void TestGraph() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix4.txt");
    assert(graph.getEdgesCount() == 45);
    assert(graph.getGraphType() == ng::GraphType::kUndirectedGraph);
    std::cout << "Graph edges count: " << graph.getEdgesCount() << std::endl;
}

int main() {
    TestGraph();
}