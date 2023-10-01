cmake_minimum_required(VERSION 3.5...3.16)
project(matrix_matrix LANGUAGES CXX)

add_library(matrix_matrix INTERFACE)
add_library(Matrix::matrix ALIAS matrix_matrix)

target_include_directories(matrix_matrix INTERFACE include)

target_link_libraries(matrix_matrix
    INTERFACE
        Matrix::matrix_state
        Matrix::matrix_normal_iterator
        Matrix::matrix_reverse_iterator
)
