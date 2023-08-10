#include "controller.h"

namespace ng {
    void Controller::LoadGraphFromFile(std::string_view file_path) {
        model_->LoadGraphFromFile(file_path);
    }

    void Controller::ExportGraphToDot(std::string_view file_path) {
        model_->ExportGraphToDot(file_path);
    }

    std::vector<std::size_t> Controller::BreadthFirstSearch(std::size_t start_vertex) {
        return model_->BreadthFirstSearch(start_vertex);
    }

    std::vector<std::size_t> Controller::DepthFirstSearch(std::size_t start_vertex) {
        return model_->DepthFirstSearch(start_vertex);
    }

    double Controller::GetShortestPathBetweenVertices(std::size_t vertex1, std::size_t vertex2) {
        return model_->GetShortestPathBetweenVertices(vertex1, vertex2);
    }

    Matrix<double> Controller::GetShortestPathBetweenAllVertices() {
        return model_->GetShortestPathBetweenAllVertices();
    }

    Matrix<double> Controller::GetLeastSpanningTree() {
        return model_->GetLeastSpanningTree();
    }

    TsmProblem<double> Controller::SolveTravelingSalesmanProblem() {
        return model_->SolveTravelingSalesmanProblem();
    }

    void Controller::PrintGraph() {
        model_->PrintGraph();
    }
}