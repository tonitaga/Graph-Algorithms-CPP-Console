#ifndef GRAPHALGORITHMS_MODEL_H
#define GRAPHALGORITHMS_MODEL_H

#include "graph_algorithms.h"

namespace ng {
    class Model {
    public:
        Model() noexcept = default;

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
        Graph<double> graph_;
    };
}

#endif //GRAPHALGORITHMS_MODEL_H
