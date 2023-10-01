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

4.1 Test Library before install

```shell
   make test
```

4.2 Install library

```shell
   make install
```

5. Create empty file main.cc and paste the code

```cpp
#include <matrix/matrix.h>
#include <matrix/static_matrix.h>

using namespace ng;

int main() {
    Matrix<int> matrix1(3, 3, 2);
    StaticMatrix<int, 3, 3> matrix2(3);
    print(matrix1, matrix2);
    return EXIT_SUCCESS;
}
```

6. Compile file

```shell
   g++ -std=c++20 -Wall -Werror -Wextra main.cc -o use_matrix
```

7. Run compiled file

```shell
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
   cd Matrix-Library-CPP
   git checkout main
   cd code_samples
```

## Rode map

* In v1.0 version of the Matrix-Library-CPP will be fixed most bugs of Library. (Estimated completion time to October 3, 2023)
* In v1.1 version of the Matrix-Library-CPP it will be possible to use not only C++20 standard but also older standards. (Estimated completion time to October 10, 2023)