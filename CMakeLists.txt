cmake_minimum_required(VERSION 3.5...3.16)
project(Matrix_Library_CPP_TEST LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-but-set-variable")

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
        matrix
)

add_executable(Matrix_Library_CPP_TEST
        tests/reverse_iterator_test.cc
        tests/normal_iterator_test.cc
        tests/matrix_test.cc
        tests/static_matrix_test.cc
)
target_link_libraries(Matrix_Library_CPP_TEST gtest_main)
add_test(NAME Matrix_Library_CPP_TEST_ COMMAND Matrix_Library_CPP_TEST)
