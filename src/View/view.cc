#include "view.h"

namespace ng {
    enum class Choice : int {
        kExit,
        kLoadGraphFromFile,
        kBreadthFirstSearch,
        kDepthFirstSearch,
        kGetShortestPathBetweenVertices,
        kGetShortestPathsBetweenAllVertices,
        kGetLeastSpanningTree,
        kSolveTravelingSalesmanProblem,
        kExportGraphToDot,
        kPrintGraph
    };

    void View::Start() {
        bool exit_flag = false;
        while (!exit_flag) {
            DisplayMenu();
            int ch = PerformChoice();
            if ((Choice)ch == Choice::kLoadGraphFromFile) {
                controller_->LoadGraphFromFile(PerformStringInput());
                controller_->PrintGraph();
            } else if ((Choice)ch == Choice::kBreadthFirstSearch) {
                DisplayVector(controller_->BreadthFirstSearch(PerformIntInput()));
            } else if ((Choice)ch == Choice::kDepthFirstSearch) {
                DisplayVector(controller_->DepthFirstSearch(PerformIntInput()));
            } else if ((Choice)ch == Choice::kGetShortestPathBetweenVertices) {
                std::cout << "Shortest path is: " <<
                            controller_->GetShortestPathBetweenVertices(PerformIntInput(), PerformIntInput()) << std::endl;
            } else if ((Choice)ch == Choice::kGetShortestPathsBetweenAllVertices) {
                DisplayMatrix(controller_->GetShortestPathBetweenAllVertices());
            } else if ((Choice)ch == Choice::kGetLeastSpanningTree) {
                DisplayMatrix(controller_->GetLeastSpanningTree());
            } else if ((Choice)ch == Choice::kSolveTravelingSalesmanProblem) {
                DisplayTsmProblem(controller_->SolveTravelingSalesmanProblem());
            } else if ((Choice)ch == Choice::kExportGraphToDot) {
                controller_->ExportGraphToDot(PerformStringInput());
            } else if ((Choice)ch == Choice::kPrintGraph) {
                controller_->PrintGraph();
            } else if ((Choice)ch == Choice::kExit) {
                exit_flag = true;
            } else {
                std::cout << std::endl <<
                          "Wrong menu item number!" << std::endl <<
                          "Press any key to try again." << std::endl;
                std::cin.get();
            }
        }
    }

    void View::DisplayMenu() {
        std::cout << "=========" << std::endl;
        std::cout << " M E N U " << std::endl;
        std::cout << "=========" << std::endl;
        std::cout << "1. Load graph from file" << std::endl;
        std::cout << "2. Breadth first search" << std::endl;
        std::cout << "3. Depth first search" << std::endl;
        std::cout << "4. Get shortest path between vertices" << std::endl;
        std::cout << "5. Get shortest paths between all vertices" << std::endl;
        std::cout << "6. Get least spanning tree" << std::endl;
        std::cout << "7. Solve traveling salesman problem" << std::endl;
        std::cout << "8. Export graph to .dot file" << std::endl;
        std::cout << "9. Print current graph" << std::endl;
        std::cout << "0. Quit" << std::endl << std::endl;
    }

    int View::PerformChoice() {
        int choice = 0;
        std::cout << "Input a menu item digit: ";
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input Error, try again." << std::endl;
        }
        return choice;
    }

    int View::PerformIntInput() {
        int number;
        std::cout << "Input a decimal number: ";
        while (!(std::cin >> number)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input Error, try again." << std::endl;
        }
        return number;
    }

    std::string View::PerformStringInput() {
        std::string str;
        std::cout << "Input a path to file: ";
        std::cin >> str;
        return str;
    }

    void View::DisplayVector(const std::vector<std::size_t> &v) {
        std::cout << std::endl;
        std::cout << "Path: ";
        for (auto element : v) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    void View::DisplayMatrix(const Matrix<double> &m) {
        std::cout << "Answer is:\n";
        std::cout << m << std::endl;
    }

    void View::DisplayTsmProblem(const TsmProblem<double> &tsm) {
        std::cout << "Salesman's problem\n";
        std::cout << "Found distance: " << tsm.distance << std::endl;
        DisplayVector(tsm.vertices);
    }
}