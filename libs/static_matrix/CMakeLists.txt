cmake_minimum_required(VERSION 3.5...3.16)
project(matrix_static_matrix LANGUAGES CXX)

add_library(matrix_static_matrix INTERFACE)
add_library(Matrix::static_matrix ALIAS matrix_static_matrix)

target_include_directories(matrix_static_matrix INTERFACE include)

target_link_libraries(matrix_static_matrix
    INTERFACE
        Matrix::matrix_state
        Matrix::matrix_normal_iterator
        Matrix::matrix_reverse_iterator
)
