cmake_minimum_required(VERSION 3.26)
project(Matrix_Library_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall")

include_directories(
        ${PROJECT_SOURCE_DIR}/code_samples
        ${PROJECT_SOURCE_DIR}/src/matrix/include
        ${PROJECT_SOURCE_DIR}/src/matrix/include/implementation
)

add_executable(Matrix_Library_CPP
        code_samples/compile_time.cc
        src/matrix/include/matrix
        src/matrix/include/implementation/matrix.h
        src/matrix/include/implementation/matrix.tpp
        src/matrix/include/implementation/matrix_normal_iterator.h
)
