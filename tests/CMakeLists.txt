cmake_minimum_required(VERSION 3.5...3.16)
project(mtl-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-unused-but-set-variable")
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
        fundamental_types/adapters_test.cc
        fundamental_types/atomic_matrix_test.cc
        fundamental_types/reverse_iterator_test.cc
        fundamental_types/normal_iterator_test.cc
        fundamental_types/matrix_test.cc
        fundamental_types/static_matrix_test.cc
        fundamental_types/stl_algo_matrix_test.cpp
        fundamental_types/type_traits_test.cc
        fundamental_types/atomic_matrix_test.cc
        non_fundamental_types/matrix_test.cc
)

target_link_libraries(${PROJECT_NAME} gtest_main)
add_test(NAME ${PROJECT_NAME}_ COMMAND ${PROJECT_NAME})
