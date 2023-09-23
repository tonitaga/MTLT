cmake_minimum_required(VERSION 3.26)
project(Matrix_Library_CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra")

include_directories(
        ${PROJECT_SOURCE_DIR}/src/matrix/include
        ${PROJECT_SOURCE_DIR}/src/matrix/include/implementation
)

add_executable(Matrix_Library_CPP
        src/main.cc
        src/matrix/include/matrix.h
        src/matrix/include/implementation/matrix.tpp
        src/matrix/include/implementation/matrix_normal_iterator.h
)
