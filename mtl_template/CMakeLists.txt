cmake_minimum_required(VERSION 3.5...3.16)
project(mtl-template)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/install.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20")

add_executable(${PROJECT_NAME} src/main.cc)
