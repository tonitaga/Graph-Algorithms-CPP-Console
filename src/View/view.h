#ifndef GRAPHALGORITHMS_VIEW_H
#define GRAPHALGORITHMS_VIEW_H

#include "controller.h"

namespace ng {
    class View {
    public:
        explicit View(Controller *controller) : controller_(controller) {};

        void Start();

    private:
        Controller *controller_ = nullptr;

        void DisplayMenu();
        void DisplayMatrix(const Matrix<double> &m);
        void DisplayVector(const std::vector<std::size_t> &v);
        void DisplayTsmProblem(const TsmProblem<double> &tsm);

        int PerformIntInput();
        int PerformChoice();
        std::string PerformStringInput();
    };
}

#endif //GRAPHALGORITHMS_VIEW_H
