cmake_minimum_required(VERSION 3.5...3.16)
project(mtl)

set(CMAKE_CXX_STANDARD 17)

set(MTL_INCLUDE_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/include/mtl)

add_library(${PROJECT_NAME} SHARED
        ${MTL_INCLUDE_LOCATION}/matrix.h
        ${MTL_INCLUDE_LOCATION}/matrix_state.h
        ${MTL_INCLUDE_LOCATION}/matrix_config.h
        ${MTL_INCLUDE_LOCATION}/static_matrix.h
        ${MTL_INCLUDE_LOCATION}/matrix_normal_iterator.h
        ${MTL_INCLUDE_LOCATION}/matrix_reverse_iterator.h
        ${MTL_INCLUDE_LOCATION}/experimental/print.h
        ${MTL_INCLUDE_LOCATION}/experimental/matrix.h
        ${MTL_INCLUDE_LOCATION}/experimental/atomic_matrix.h
        ${MTL_INCLUDE_LOCATION}/experimental/static_matrix.h
        ${MTL_INCLUDE_LOCATION}/experimental/matrix_type_traits.h
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)