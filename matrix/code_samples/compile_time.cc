#include "../static_matrix.h"

//
// Compile time initialization and computation since c++17 standard
//

#define CXX17_TAGS MATRIX_CXX17_UNUSED MATRIX_CXX17_CONSTEXPR
#define CXX23_TAGS MATRIX_CXX17_UNUSED MATRIX_CXX23_CONSTEXPR

int main() {
    // Compile time creation and initialization of static_matrix class
    CXX17_TAGS mtl::static_matrix<int, 3, 3> matrix({
       1, 2, 3,
       4, 5, 6,
       7, 8, 9
    });

    // Compile time copy
    CXX17_TAGS mtl::static_matrix<int, 3, 3> copied = matrix;

    // Compile time transformations
    CXX17_TAGS auto add1 = matrix + 2;
    CXX17_TAGS auto sub1 = matrix - 2;
    CXX17_TAGS auto mul1 = matrix * 2;
    CXX17_TAGS auto div1 = matrix / 2;
    CXX17_TAGS auto add2 = matrix.add(mtl::static_matrix<int, 3, 3>(2));
    CXX17_TAGS auto sub2 = matrix.sub(mtl::static_matrix<int, 3, 3>(2));
    CXX17_TAGS auto mul2 = matrix.mul_by_element(mtl::static_matrix<int, 3, 3>(2));
    CXX17_TAGS auto div2 = matrix.div_by_element(mtl::static_matrix<int, 3, 3>(2));
    CXX17_TAGS auto minor = matrix.minor(0, 0);
    CXX17_TAGS auto transpose = matrix.transpose();
    CXX17_TAGS auto trace = matrix.trace();

    // transforming values under matrices for floating_point types (Since c++23)
    CXX23_TAGS auto round = matrix.round();
    CXX23_TAGS auto floor = matrix.floor();
    CXX23_TAGS auto ceil = matrix.ceil();

    // Identity
    CXX17_TAGS auto identity = matrix.identity();

    // Converting to other type
    CXX17_TAGS auto double_m = matrix.convert_to<double>();
    // ... //

    // Determinants
    CXX17_TAGS auto det1 = matrix.determinant_laplacian();
    CXX17_TAGS auto det2 = matrix.determinant_gaussian();

    CXX17_TAGS auto less1 = det1 <= mtl::matrix_epsilon<double>::epsilon;
    CXX17_TAGS auto less2 = det2 <= mtl::matrix_epsilon<double>::epsilon;

    // Other matrix transformation from linear algebra
    CXX17_TAGS auto minor_item = matrix.minor_item(0, 0);
    CXX17_TAGS auto complements = matrix.calc_complements();
    CXX17_TAGS auto inverse = matrix.convert_to<double>().inverse();

    // Equality
    CXX17_TAGS auto is_equal = matrix == mtl::static_matrix<int, 3, 3>(2);
}