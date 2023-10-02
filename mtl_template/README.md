# Template project using MTL

---

## MTL - Matrix Template Library


- Library provides a wide range of possibilities for working with matrices
- MTL is a header-only library
- Has easy integration into your project

---

## Integration

- Just copy all files in folder **mtl-template** into your empty project

### Install path configure

install.cmake file
```cmake
set(MTL_INSTALL_PATH src/extern)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH})
execute_process(
        COMMAND git clone --branch v1.2 "https://github.com/tonitaga/Matrix-Library-CPP.git" mtl
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}
)

execute_process(
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}/mtl/matrix ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}
        COMMAND rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH}/mtl
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${MTL_INSTALL_PATH})
```

- **MTL_INSTALL_PATH** is an install math of MTL headers
- if is need change **src/extern** to your own path 

### CMakeLists.txt configure

CMakeLists.txt file

```cmake
cmake_minimum_required(VERSION 3.5...3.16)
project(mtl-template)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/install.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++20")

add_executable(${PROJECT_NAME} src/main.cc)
```

- if is need change **mtl-template** project name to your own one
- if is need change **CMAKE_CXX_STANDARD** from **20** to one of **[17 14 11]** 
- if is need change **CMAKE_CXX_FLAGS** to your own compiler flags
- if is need add your own executable files

### Makefile configure

Makefile file
```makefile
BUILD_FOLDER_NAME="build"
CMAKE_PROJECT_NAME="mtl-template"
MTL_INSTALL_PATH="src/extern"

install_mtl:
	@cmake -S . -B ${BUILD_FOLDER_NAME}

build: install_mtl
	@cmake --build ${BUILD_FOLDER_NAME}

run:
	@${BUILD_FOLDER_NAME}/${CMAKE_PROJECT_NAME}

clean:
	@rm -rf ${BUILD_FOLDER_NAME}

uninstall_mtl:
	@rm -rf ${MTL_INSTALL_PATH}
```

- if is need change **BUILD_FOLDER_NAME** to your own build folder name
- Set project name from CMakeLists.txt to **CMAKE_PROJECT_NAME**
- Set MTL install path from install.cmake to **MTL_INSTALL_PATH**