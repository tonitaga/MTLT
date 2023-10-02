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
   git checkout origin/v1.1
```

4. To install library use makefile

4.1 Test Library before install

```shell
   make test
```

4.2 Install library

* Need sudo before main in MacOS and Linux
```shell
   make install
```

5. Create empty file main.cc and paste the code

```cpp
#include <matrix/matrix.h>
#include <matrix/static_matrix.h>

int main() {
    ng::matrix<int> matrix1(3, 3, 1);
    ng::static_matrix<int, 3, 3> matrix2(1);

    int trace1 = matrix1.trace();
    int trace2 = matrix2.trace();

    int determinant1 = matrix1.determinant();
    int determinant2 = matrix2.determinant();

    matrix1.fill_random(1, 9);
    matrix2.fill_random(1, 9);

    auto inverse1 = matrix1.convert_to<double>().inverse();
    auto inverse2 = matrix2.convert_to<double>().inverse();

    auto complements1 = matrix1.calc_complements();
    auto complements2 = matrix2.calc_complements();

    ng::print(trace1, trace2,
              determinant1, determinant2,
              matrix1, matrix2,
              inverse1, inverse2,
              complements1, complements2);
    return EXIT_SUCCESS;
}
```

6. Compile file

* Using C++20 Standard
```shell
   g++ -std=c++20 -Wall -Werror -Wextra main.cc -o use_matrix
```

* Using C++17 Standard
```shell
   g++ -std=c++17 -Wall -Werror -Wextra main.cc -o use_matrix
```

* Using C++14 Standard
```shell
   g++ -std=c++14 -Wall -Werror -Wextra main.cc -o use_matrix
```

* Using C++11 Standard
```shell
   g++ -std=c++11 -Wall -Werror -Wextra main.cc -o use_matrix
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

* Need sudo before main in MacOS and Linux
```shell
   make uninstall
```

## Rode map

* In v1.0 version of the Matrix-Library-CPP will be fixed most bugs of Library. (Estimated completion time to October 3, 2023)
* In v1.1 version of the Matrix-Library-CPP it will be possible to use not only C++20 standard but also older standards. (Estimated completion time to October 10, 2023)
* In v1.2 version of the Matrix-Library-CPP it will be possible to use not only fundamental types ((Estimated completion time to October 20, 2023)
