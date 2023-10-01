cmake_minimum_required(VERSION 3.5...3.16)
project(matrix_matrix_normal_iterator LANGUAGES CXX)

add_library(matrix_matrix_normal_iterator INTERFACE)
add_library(Matrix::matrix_normal_iterator ALIAS matrix_matrix_normal_iterator)

target_include_directories(matrix_matrix_normal_iterator INTERFACE include)
