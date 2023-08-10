#ifndef GRAPHALGORITHMS_FILE_MANAGER_H
#define GRAPHALGORITHMS_FILE_MANAGER_H

#include <string_view>

#include "matrix.h"
#include "graph_help.h"

namespace ng {
    class FileManager final {
    public:
        template<typename T>
        static Matrix<T> ReadMatrixFromFile(std::string_view path);

        template<typename T>
        static void ExportGraphToDot(const std::vector<GraphEdge<T>> &edges, GraphType graph_type, std::string_view save_path);
    };
}

#include "file_manager.tpp"

#endif //!GRAPHALGORITHMS_FILE_MANAGER_H
