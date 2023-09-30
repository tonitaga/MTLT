cmake_minimum_required(VERSION 3.26)
project(Matrix_Library_CPP_TEST)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall")

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
        ../include/
        ../include/implementation/
)

add_executable(Matrix_Library_CPP_TEST unit_tests.cc)
target_link_libraries(Matrix_Library_CPP_TEST gtest_main)
add_test(NAME Matrix_Library_CPP_TEST_ COMMAND Matrix_Library_CPP_TEST)
