#include "graph.h"

#include <cassert>

void TestGraph() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix1.txt");
    assert(graph.getEdgesCount() == 7);
    std::cout << "Graph edges count: " << graph.getEdgesCount() << std::endl;
}

int main() {
    TestGraph();
}