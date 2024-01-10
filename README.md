# MTL - Matrix Template Library

## Install and Configuration

#### 1. vcpkg and cmake

```shell
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
vcpkg install mtl
```

Then configure in your project CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16...3.5)
project(PROJECT)

find_package(mtl REQUIRED)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE mtl::mtl)
```

Write simple source code in main.cc for check
```c++
#include <mtl/matrix.h>

int main() {
  mtl::matrix<int> matrix(3, 3, {
	1, 2, 3,
	4, 5, 6,
	7, 8, 9
  });
  
  mtl::print(matrix);
}
```

Build your program using cmake
```shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg_root]/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

#### 2. Install as git submodule

```shell
mkdir third_party
cd third_party
git submodule add https://github.com/tonitaga/Matrix-Template-Library-CPP.git
```

Configure CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.16...3.5)
project(PROJECT)

include_directories(third_party/Matrix-Template-Library-CPP/include)

add_executable(${PROJECT_NAME} main.cc)
```

Build your program using cmake

```shell
git submodule update --init
mkdir build
cd build
cmake ..
cmake --build .
```