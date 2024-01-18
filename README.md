# MTL - Matrix Template Library

MTL is a header-only template matrix library that supports fundamental data types, and has been C++ standard since 11

## Install and Configuration

#### 1. vcpkg and cmake

```shell
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
vcpkg install mtlt
```

Then configure in your project CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16...3.5)
project(PROJECT)

find_package(mtlt REQUIRED)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE mtlt::mtlt)
```

Write simple source code in main.cc for check
```c++
#include <mtlt/matrix.h>
#include <mtlt/print.h> // For mtlt::print

int main() {
  mtlt::matrix<int> matrix(3, 3, {
	1, 2, 3,
	4, 5, 6,
	7, 8, 9
  });
  
  mtlt::print(matrix);
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
