#include "graph.h"
#include "file_manager.h"
#include "salesmans_problem.h"

#include <cassert>

void TestGraph() {
    ng::Matrix<int> matrix(ng::FileManager::ReadMatrixFromFile<int>("datasets/file_read_test/adjacency_matrix9.txt"));
    ng::Graph<int> graph(matrix);
    assert(graph.getEdgesCount() == 128);
    assert(graph.getGraphType() == ng::GraphType::kUndirectedGraph);
    std::cout << "Graph edges count: " << graph.getEdgesCount() << std::endl;
//    auto graph_edges = graph.getEdges();
//    for (const auto &edge : graph_edges)
//        std::cout << edge << std::endl;
    ng::AntColony<int> colony(graph);
    auto result = colony.SolveSalesmansProblem();
    for (auto v : result.vertices)
        std::cout << v << ' ';
    std::cout << '\n' << result.distance << std::endl;
}

int main() {
    TestGraph();
}