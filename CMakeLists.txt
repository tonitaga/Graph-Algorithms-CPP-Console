cmake_minimum_required(VERSION 3.26)
project(GraphAlgorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra")

include_directories(src/Graph/include)
include_directories(src/Graph/internal)
include_directories(src/GraphAlgorithms/include)
include_directories(src/GraphAlgorithms/internal)

add_executable(GraphAlgorithms
        src/Graph/include/file_manager.h
        src/Graph/include/graph.h
        src/Graph/include/matrix.h
        src/Graph/include/graph_edge.h
        src/GraphAlgorithms/include/graph_algorithms.h
        main.cc)

add_executable(FileReadTest
        src/Graph/include/file_manager.h
        src/Graph/include/graph.h
        src/Graph/include/matrix.h
        src/Graph/include/graph_edge.h
        src/GraphAlgorithms/include/graph_algorithms.h
        src/Tests/file_read_test.cc)

add_executable(GraphTest
        src/Graph/include/file_manager.h
        src/Graph/include/graph.h
        src/Graph/include/matrix.h
        src/Graph/include/graph_edge.h
        src/GraphAlgorithms/include/graph_algorithms.h
        src/Tests/graph_test.cc)

add_executable(GraphAlgorithmsTest
        src/Graph/include/file_manager.h
        src/Graph/include/graph.h
        src/Graph/include/matrix.h
        src/Graph/include/graph_edge.h
        src/GraphAlgorithms/include/graph_algorithms.h
        src/Tests/graph_algorithms_test.cc)
