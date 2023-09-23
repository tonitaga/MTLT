#include <iostream>
#include <vector>

#include <matrix.h>

using namespace ng;

int main() {
    FMatrix matrix(5, 5, -1);
    std::cout << matrix << std::endl;
    return EXIT_SUCCESS;
}