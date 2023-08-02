#ifndef GRAPHALGORITHMS_GRAPH_H
#define GRAPHALGORITHMS_GRAPH_H

#include "matrix.h"

namespace ng {
    template <typename T>
    class Graph final {
        static_assert(std::is_fundamental<T>::value == true,
                      "Template parameter T must be fundamental");
    };
}

#endif //GRAPHALGORITHMS_GRAPH_H
