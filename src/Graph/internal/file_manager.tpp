#ifndef GRAPHALGORITHMS_FILE_MANAGER_TPP
#define GRAPHALGORITHMS_FILE_MANAGER_TPP

#include "file_manager.h"

namespace ng {
    template<typename T>
    Matrix<T> FileManager::ReadMatrixFromFile(std::string_view path) {
        static_assert(std::is_fundamental<T>::value, "Template parameter T must be fundamental");
        Matrix<T> read_data;
        try {
            std::ifstream file(path.data());

            if (!file.is_open()) {
                std::cerr << "FileManager::ReadMatrixFromFile:\n\tError: File doesn't exists.\n\tPath:  " << path << std::endl;
                return {};
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
            read_data = {};
        }

        return read_data;
    }
}

#endif //GRAPHALGORITHMS_FILE_MANAGER_TPP
