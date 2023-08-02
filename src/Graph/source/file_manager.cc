#include "file_manager.h"

#include <fstream>
#include <iostream>

namespace ng {
    template<typename T>
    Matrix<T> FileManager::ReadMatrixFromFile(std::string_view path) {
        Matrix<T> read_data;
        try {
            std::ifstream file(path.data());

            if (!file.is_open()) {
                std::cerr << "FileManager::ReadMatrixFromFile -> File doesn't exists." << std::endl;
                return Matrix<T>::matrix_empty;
            }

            std::size_t square_size;
            file >> square_size;

            Matrix<T> data(square_size);
            for (std::size_t row = 0; row != square_size; ++row)
                for (std::size_t col = 0; col != square_size; ++col)
                    file >> data(row, col);

            read_data = std::move(data);

        } catch (std::exception &exception) {
            std::cerr << exception.what() << std::endl;
            read_data = Matrix<T>::matrix_empty;
        }

        return read_data;
    }
}
