cmake_minimum_required(VERSION 3.26)
project(GraphAlgorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra")

include_directories(src/Graph/include)
include_directories(src/GraphAlgorithms/include)
include_directories(src/Graph/internal)
include_directories(src/GraphAlgorithms/internal)

file(GLOB_RECURSE HEADER_FILES
        "${PROJECT_SOURCE_DIR}/src/*.h"
)

add_executable(GraphAlgorithms
        ${HEADER_FILES}
        main.cc)

add_executable(FileReadTest
        ${HEADER_FILES}
        src/Tests/file_read_test.cc)

add_executable(GraphTest
        ${HEADER_FILES}
        src/Tests/graph_test.cc)

add_executable(GraphAlgorithmsTest
        ${HEADER_FILES}
        src/Tests/graph_algorithms_test.cc)

add_executable(GraphDotExportTest
        ${HEADER_FILES}
        src/Tests/graph_dot_save_test.cc)
