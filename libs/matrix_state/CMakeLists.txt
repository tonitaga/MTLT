cmake_minimum_required(VERSION 3.5...3.16)
project(matrix_matrix_state LANGUAGES CXX)

add_library(matrix_matrix_state INTERFACE)
add_library(Matrix::matrix_state ALIAS matrix_matrix_state)

target_include_directories(matrix_matrix_state INTERFACE include)
