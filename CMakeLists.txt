cmake_minimum_required(VERSION 3.26)
project(GraphAlgorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra")

include_directories(src/Graph/include)
include_directories(src/GraphAlgorithms/include)

add_executable(GraphAlgorithms
        src/Graph/include/file_manager.h
        src/Graph/include/graph.h
        src/Graph/include/matrix.h
        src/Graph/source/file_manager.cc
        src/Graph/source/graph.cc
        src/Graph/source/matrix.cc
        src/GraphAlgorithms/include/graph_algorithms.h
        src/GraphAlgorithms/source/graph_algorithms.cc
        main.cc)
