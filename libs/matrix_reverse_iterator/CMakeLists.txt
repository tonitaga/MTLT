cmake_minimum_required(VERSION 3.5...3.16)
project(matrix_matrix_reverse_iterator LANGUAGES CXX)

add_library(matrix_matrix_reverse_iterator INTERFACE)
add_library(Matrix::matrix_reverse_iterator ALIAS matrix_matrix_reverse_iterator)

target_include_directories(matrix_matrix_reverse_iterator INTERFACE include)
