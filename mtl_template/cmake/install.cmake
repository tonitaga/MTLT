set(MTL_INSTALL_PATH src/extern)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH})
execute_process(
        COMMAND git clone --branch v1.2 "https://github.com/tonitaga/Matrix-Template-Library-CPP.git" mtl
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}
)

execute_process(
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}/mtl/matrix ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}
        COMMAND rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}/mtl
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH})