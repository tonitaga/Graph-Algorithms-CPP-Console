#include <iostream>

#include "graph.h"
#include "file_manager.h"

void ExportToDotGraph() {
    std::string root_directory = R"(D:\Github\Console\GraphAlgorithms\datasets\file_read_test\)";
    int index = 1;
    for (const auto &path : {"datasets/file_read_test/adjacency_matrix1.txt",
                             "datasets/file_read_test/adjacency_matrix2.txt",
                             "datasets/file_read_test/adjacency_matrix3.txt",
                             "datasets/file_read_test/adjacency_matrix4.txt",
                             "datasets/file_read_test/adjacency_matrix5.txt",
                             "datasets/file_read_test/adjacency_matrix9.txt"}) {
        ng::Graph<int> graph(ng::FileManager::ReadMatrixFromFile<int>(path));
        graph.ExportGraphToDot(root_directory + "dot_graph" + std::to_string(index++) + ".dot");
        std::cout << std::setw(6) << graph << std::endl;
    }
}

int main() {
    ExportToDotGraph();
}