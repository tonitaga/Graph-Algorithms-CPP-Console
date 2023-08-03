#ifndef GRAPHALGORITHMS_FILE_MANAGER_TPP
#define GRAPHALGORITHMS_FILE_MANAGER_TPP

#include "file_manager.h"

#include <fstream>
#include <iostream>

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

    template<typename T>
    void FileManager::ExportGraphToDot(const Graph<T> &graph, std::string_view save_path, std::string_view graph_name) {
        try {
            if (graph.isEmpty()) {
                std::cerr << "FileManager::ExportGraphToDot:\n\t" <<
                          "Error: Nothing to save, graph is empty\n\t" << "Path:  " << save_path << std::endl;
                return;
            }

            const auto graph_type = graph.getGraphType();
            if (graph_type == GraphType::kMultiGraph) {
                std::cerr << "FileManager::ExportGraphToDot:\n\t" <<
                          "Error: Can't save multi graph into .dot style file\n\tPath:  " << save_path << std::endl;
                return;
            }

            std::ofstream file(save_path.data());
            if (!file.is_open()) {
                std::cerr << "FileManager::ExportGraphToDot:\n\t" <<
                             "Error: Can't create or open file to write\n\tPath:  " << save_path << std::endl;
                return;
            }

            std::string arrow = " -> ";
            if (graph_type == GraphType::kUndirectedGraph) {
                file << "graph " << graph_name << " {\n";
                arrow = " -- ";
            } else
                file << "digraph " << graph_name << " {\n";

            file << "\tlayout=circo\n";

            auto graph_edges = graph.getEdges();
            for (const GraphEdge<T>& edge : graph_edges) {
                file << "\t" << edge.from + 1 << arrow << edge.to + 1;
                if (edge.weight != 1) {
                    file << " [label=\"" << edge.weight << "\"]";
                }
                file << '\n';
            }

            file << "}\n";
            file.close();

        } catch (std::exception &exception) {
            std::cerr << exception.what() << std::endl;
        }
    }
}

#endif //GRAPHALGORITHMS_FILE_MANAGER_TPP
