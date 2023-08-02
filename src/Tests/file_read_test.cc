#include "file_manager.h"

void FileReadTest() {
    for (const auto &path : {"datasets/file_read_test/adjacency_matrix1.txt",
                             "datasets/file_read_test/adjacency_matrix2.txt",
                             "datasets/file_read_test/adjacency_matrix3.txt",
                             "datasets/file_read_test/adjacency_matrix4.txt",
                             "datasets/file_read_test/adjacency_matrix5.txt"})
        auto read_data = ng::FileManager::ReadMatrixFromFile<int>(path);
}

int main() {
    FileReadTest();
}
