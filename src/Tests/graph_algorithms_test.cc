#include "graph_algorithms.h"

#include <cassert>

void BFSTest() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix4.txt");
    assert(!graph.isEmpty());
    auto ender_order = ng::GraphAlgorithms::BreadthFirstSearch(graph, 1);
    std::vector<int> correct_enter_order {1, 2, 3, 6, 7, 8, 9, 11, 13, 4, 12, 14, 15, 5, 10};
    assert(ender_order == correct_enter_order);
    std::cout << "BFS Result is correct!" << std::endl;
}

void DFSTest() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix4.txt");
    assert(!graph.isEmpty());
    auto ender_order = ng::GraphAlgorithms::DepthFirstSearch(graph, 1);
    std::vector<int> correct_enter_order {1, 2, 4, 7, 11, 12, 13, 6, 9, 14, 15, 8, 5, 10, 3};
    assert(ender_order == correct_enter_order);
    std::cout << "DFS Result is correct!" << std::endl;
}

int main() {
    BFSTest();
    DFSTest();
}