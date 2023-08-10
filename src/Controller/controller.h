#ifndef GRAPHALGORITHMS_CONTROLLER_H
#define GRAPHALGORITHMS_CONTROLLER_H

#include "model.h"

namespace ng {
    class Controller {
    public:
        explicit Controller(Model *model) : model_(model) {};

        void LoadGraphFromFile(std::string_view file_path);
        void ExportGraphToDot(std::string_view file_path);

        std::vector<std::size_t> BreadthFirstSearch(std::size_t start_vertex);
        std::vector<std::size_t> DepthFirstSearch(std::size_t start_vertex);

        double GetShortestPathBetweenVertices(std::size_t vertex1, std::size_t vertex2);
        Matrix<double> GetShortestPathBetweenAllVertices();

        Matrix<double> GetLeastSpanningTree();

        TsmProblem<double> SolveTravelingSalesmanProblem();

        void PrintGraph();

    private:
        Model *model_ = nullptr;
    };
}

#endif //GRAPHALGORITHMS_CONTROLLER_H
