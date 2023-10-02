#include <matrix/matrix.h>
#include <matrix/static_matrix.h>

void show_matrix() {
    mtl::matrix<int> matrix1(3, 3, {
            1,  2,  3,
            7,  8,  9,
            13, 14, 15
    });

    mtl::matrix<int> matrix2(3, 3, {
            4, 5, 6,
            10, 11, 12,
            16, 17, 18
    });

    mtl::matrix<int> join_right = matrix1.join_right(matrix2);
    mtl::print(matrix1, matrix2, join_right);
}

void show_static_matrix() {
    mtl::static_matrix<int, 3, 3> matrix1({
            1,  2,  3,
            7,  8,  9,
            13, 14, 15
    });

    mtl::static_matrix<int, 3, 3> matrix2({
            4, 5, 6,
            10, 11, 12,
            16, 17, 18
    });

    mtl::static_matrix<int, 3, 6> join_right = matrix1.join_right(matrix2);
    mtl::print(matrix1, matrix2, join_right);
}

int main() {
    show_matrix();
    show_static_matrix();
    return EXIT_SUCCESS;
}
