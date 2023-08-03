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

void DijkstraTest() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix4.txt");
    assert(!graph.isEmpty());
    int shortest_path = ng::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 5);
    assert(shortest_path == 2);
    std::cout << "DijkstraAlgorithm Result is correct!" << std::endl;
}

void FLoydWorshellTest() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix4.txt");
    assert(!graph.isEmpty());
    ng::Matrix<int> distance_matrix = ng::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
    ng::Matrix<int> correct_answer = ng::FileManager::ReadMatrixFromFile<int>("datasets/floyd_worshell/floyd_adjacency_matrix4.txt");
    assert(distance_matrix == correct_answer);
    std::cout << "FLoydWorshellAlgorithm Result is correct!" << std::endl;
}

void PrimTest() {
    ng::Graph<int> graph("datasets/file_read_test/adjacency_matrix4.txt");
    assert(!graph.isEmpty());
    ng::Matrix<int> spanning_tree = ng::GraphAlgorithms::GetLeastSpanningTree(graph);
    std::cout << spanning_tree << std::endl;
    std::cout << "PrimAlgorithm Result is correct!" << std::endl;
}

int main() {
    BFSTest();
    DFSTest();
    DijkstraTest();
    FLoydWorshellTest();
    PrimTest();
}