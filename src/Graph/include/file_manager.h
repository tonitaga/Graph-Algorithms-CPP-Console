#ifndef GRAPHALGORITHMS_FILE_MANAGER_H
#define GRAPHALGORITHMS_FILE_MANAGER_H

#include <string_view>

#include "graph.h"

namespace ng {
    class FileManager final {
    public:
        template<typename T>
        static Matrix<T> ReadMatrixFromFile(std::string_view path);

        template<typename T>
        static void ExportGraphToDot(const Graph<T> &graph, std::string_view save_path, std::string_view graph_name = "Untitled");
    };
}

#include "file_manager.tpp"

#endif //!GRAPHALGORITHMS_FILE_MANAGER_H
