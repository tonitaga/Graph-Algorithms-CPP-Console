#ifndef GRAPHALGORITHMS_FILE_MANAGER_H
#define GRAPHALGORITHMS_FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <string_view>

#include "matrix.h"

namespace ng {
    class FileManager final {
    public:
        template<typename T>
        static Matrix<T> ReadMatrixFromFile(std::string_view path);
    };
}

#include "file_manager.tpp"

#endif //GRAPHALGORITHMS_FILE_MANAGER_H
