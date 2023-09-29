#include "static_matrix"

using namespace ng;

int main() {
    //
    // Static matrix support also compile time initialization
    //

    using size_type = Matrix3x3<int>::size_type;
    using value_type = Matrix3x3<int>::value_type;

    constexpr Matrix3x3<int> matrix1({
       1, 2, 3,
       4, 5, 6,
       7, 8, 9
    });

    constexpr Matrix3x3<int> matrix2({
        9, 8, 7,
        6, 5, 4,
        3, 2, 1
    });

    // Also supports mul add sub div operations and other in compile time with matrix
    constexpr StaticMatrix mul1 = matrix1.mul(matrix2);
    constexpr StaticMatrix add1 = matrix1.add(matrix2);
    constexpr StaticMatrix sub1 = matrix1.sub(matrix2);

    // If you need to operate your constexpr matrix with some value you can do this:
    constexpr Matrix3x3<int> two(2); // create matrix container only one values

    constexpr StaticMatrix mul2 = matrix1.mul_by_element(two);
    constexpr StaticMatrix add2 = matrix1.add(two);
    constexpr StaticMatrix sub2 = matrix1.sub(two);
    constexpr StaticMatrix div1 = matrix1.div_by_element(two);

    // Also you can get transposed matrix and minor matrix
    constexpr StaticMatrix transposed = matrix1.transpose();
    constexpr StaticMatrix minored = matrix1.minor(0, 0);

    // Useful for floating point types
    _GLIBCXX23_CONSTEXPR StaticMatrix round = matrix1.round();
    _GLIBCXX23_CONSTEXPR StaticMatrix floor = matrix1.floor();
    _GLIBCXX23_CONSTEXPR StaticMatrix ceil  = matrix1.ceil();

    // Also data access is compile time useful
    constexpr size_type size = matrix1.size();
    constexpr size_type cols = matrix1.cols();
    constexpr size_type rows = matrix1.rows();

    constexpr value_type sum = matrix1.sum();
    constexpr value_type m00 = matrix1(0, 0);
    // ... //
    constexpr value_type m22 = matrix1(2, 2);
}