#include "matrix/static_matrix.h"

int main() {
    ng::static_matrix<int, 3, 3> matrix({1, 2, 3, 4, 5, 6, 7, 8, 9});
    ng::print(matrix);
    return EXIT_SUCCESS;
}