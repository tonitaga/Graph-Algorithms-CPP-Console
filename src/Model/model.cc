#include "model.h"

namespace ng {
    void Model::LoadGraphFromFile(std::string_view file_path) {
        graph_.LoadGraphFromFile(file_path);
    }

    void Model::ExportGraphToDot(std::string_view file_path) {
        graph_.ExportGraphToDot(file_path);
    }

    std::vector<std::size_t> Model::BreadthFirstSearch(std::size_t start_vertex) {
        return GraphAlgorithms::BreadthFirstSearch(graph_, start_vertex);
    }

    std::vector<std::size_t> Model::DepthFirstSearch(std::size_t start_vertex) {
        return GraphAlgorithms::DepthFirstSearch(graph_, start_vertex);
    }

    double Model::GetShortestPathBetweenVertices(std::size_t vertex1, std::size_t vertex2) {
        return GraphAlgorithms::GetShortestPathBetweenVertices(graph_, vertex1, vertex2);
    }

    Matrix<double> Model::GetShortestPathBetweenAllVertices() {
        return GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_);
    }

    Matrix<double> Model::GetLeastSpanningTree() {
        return GraphAlgorithms::GetLeastSpanningTree(graph_);
    }

    TsmProblem<double> Model::SolveTravelingSalesmanProblem() {
        return GraphAlgorithms::SolveSalesmansProblem(graph_);
    }

    void Model::PrintGraph() {
        std::cout << graph_ << std::endl;
    }
}