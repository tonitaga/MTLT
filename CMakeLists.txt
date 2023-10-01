cmake_minimum_required(VERSION 3.5..3.16)
project(matrix_library LANGUAGES CXX)

add_subdirectory(libs/matrix)
add_subdirectory(libs/matrix_normal_iterator)
add_subdirectory(libs/matrix_reverse_iterator)
add_subdirectory(libs/matrix_state)
add_subdirectory(libs/static_matrix)

add_library(matrix_library INTERFACE)
add_library(Matrix::matrix_library ALIAS matrix_library)

target_include_directories(matrix_library
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/matrix/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/matrix_normal_iterator/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/matrix_reverse_iterator/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/matrix_state/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/static_matrix/include
)

target_link_libraries(matrix_library
    INTERFACE
        Matrix::matrix
        Matrix::matrix_normal_iterator
        Matrix::matrix_reverse_iterator
        Matrix::matrix_state
        Matrix::static_matrix
)