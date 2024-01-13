cmake_minimum_required(VERSION 3.5...3.16)
project(mtl-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wno-unused-but-set-variable")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../include)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
        reverse_iterator_test.cc
        normal_iterator_test.cc
        matrix_test.cc
        static_matrix_test.cc
        stl_algo_matrix_test.cpp
        type_traits_test.cc
)

target_link_libraries(${PROJECT_NAME} gtest_main)
add_test(NAME ${PROJECT_NAME}_ COMMAND ${PROJECT_NAME})
