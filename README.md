# Matrix Template Library

This is a C++ template matrix library that provides operations on matrices.

## Installation

To install the matrix template library, follow these steps:

1. Ensure you have the `g++` compiler installed on your system.
2. Clone or download the matrix library repository.

```shell
   git clone https://github.com/tonitaga/Matrix-Library-CPP.git
```
3. Open a terminal and navigate to the repository's root directory.

```shell
   cd Matrix-Library-CPP
   git checkout v1.0
```

4. To install library use makefile

```shell
   make install
```

5. Create empty file and use Matrix-Library-CPP

```cpp
#include <matrix>
#include <static_matrix>

using namespace ng;

int main() {
    Matrix<int> matrix1(3, 3);
    std::cout << matrix1 << std::endl;
    
    StaticMatrix<int, 3, 3> matrix2;
    std::cout << matrix2 << std::endl;
    
    return EXIT_SUCCESS;
}
```

6. Compile file and run

```shell
   g++ -std=c++20 -Wall -Werror -Wextra main.cc -o use_matrix
   ./use_matrix
```

## Uninstallation

To uninstall the matrix template library, follow these steps:

1. Open a terminal and navigate to the repository's root directory.

```shell
   cd Matrix-Library-CPP
```

2. To uninstall library use makefile

```shell
   make uninstall
```

## Code Samples

You can see the Matrix-Library-CPP code samples in Matrix-Library-CPP/code_samples folder

```shell
   cd Matrix-Library-CPP/code_samples
```

## Rode map

In v1.1 version of the Matrix-Library-CPP it will be possible to use not only C++20 standard but also older standards.
Estimated completion time to October 10, 2023
