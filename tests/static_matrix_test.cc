#include <gtest/gtest.h>

#include "static_matrix.h"

using namespace mtl;

TEST(StaticMatrix, Sizedmatrix) {
    static_matrix<int, 3, 3> m(5);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 5);
}

TEST(StaticMatrix, arrayConstructor) {
    static_matrix<int, 3, 3> m({1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(StaticMatrix, containerConstructor) {
    static_matrix<int, 3, 3> m(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(StaticMatrix, IdentityMethod) {
    static_matrix<int, 3, 3> m = static_matrix<int, 3, 3>().identity();
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(2, 2), 1);
}

TEST(StaticMatrix, CopyConstructor) {
    static_matrix<int, 3, 3> m1({1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 3, 3> m2 = m1;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 9);
}

TEST(StaticMatrix, CopyAssignment) {
    static_matrix<int, 3, 3> m1({1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 3, 3> m2;
    m2 = m1;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 9);
}

TEST(StaticMatrix, transformUnary) {
    static_matrix<int, 3, 3> m({1, 2, 3, 4, 5, 6, 7, 8, 9});
    m.transform([](const int &item) { return item * 2; });
    ASSERT_EQ(m(0, 0), 2);
}

TEST(StaticMatrix, transformBinary) {
    static_matrix<int, 3, 3> m1({1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 3, 3> m2({1, 2, 3, 4, 5, 6, 7, 8, 9});
    m1.transform(m2, [](const int &lhs, const int &rhs) { return lhs + rhs; });
    ASSERT_EQ(m1(2, 2), 18);
}

TEST(StaticMatrix, generate) {
    auto zero_operation = []{ return 0; };

    static_matrix<int, 3, 3> m(4);
    m.generate(zero_operation);
    ASSERT_EQ(m(0, 0), 0);
}

TEST(StaticMatrix, mathOperationsNumber) {
    static_matrix<int, 3, 3> m(10);
    m.mul(2);
    ASSERT_EQ(m(0, 0), 20);
    m.div(2);
    ASSERT_EQ(m(0, 0), 10);
    m.add(10);
    ASSERT_EQ(m(0, 0), 20);
    m.sub(10);
    ASSERT_EQ(m(0, 0), 10);

    m *= 2;
    ASSERT_EQ(m(0, 0), 20);
    m /= 2;
    ASSERT_EQ(m(0, 0), 10);
    m += 10;
    ASSERT_EQ(m(0, 0), 20);
    m -= 10;
    ASSERT_EQ(m(0, 0), 10);
}

TEST(StaticMatrix, mulmatrix) {
    static_matrix<int, 3, 3> m1({1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 3, 3> m2({9, 8, 7, 6, 5, 4, 3, 2, 1});
    static_matrix<int, 3, 3> m3 = m1.mul(m2);
    static_matrix<int, 3, 3> m4({30, 24, 18, 84, 69, 54, 138, 114, 90});

    auto begin1 = m3.begin();
    auto end1 = m3.end();
    auto begin2 = m4.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(StaticMatrix, fillRandom) {
    static_matrix<int, 3, 3> m;
    m.fill_random(5, 5);
    ASSERT_EQ(m(0, 2), 5);
}

TEST(StaticMatrix, roundItems) {
    static_matrix<double, 3, 3> m(1.9);
    m.to_round();
    auto res = std::all_of(m.begin(), m.end(), [&](const int &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);

    static_matrix<double, 3, 3> round = m.round();
    res = std::all_of(round.begin(), round.end(), [&](const int &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);
}

TEST(StaticMatrix, floorItems) {
    static_matrix<double, 3, 3> m(1.9);
    m.to_floor();
    auto res = std::all_of(m.begin(), m.end(), [&](const int &item) {
        return item == 1.0;
    });

    ASSERT_EQ(res, true);

    static_matrix<double, 3, 3> floor = m.floor();
    res = std::all_of(floor.begin(), floor.end(), [&](const int &item) {
        return item == 1.0;
    });

    ASSERT_EQ(res, true);
}

TEST(StaticMatrix, ceilItems) {
    static_matrix<double, 3, 3> m(1.001);
    m.to_ceil();
    auto res = std::all_of(m.begin(), m.end(), [&](const int &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);

    static_matrix<double, 3, 3> ceil = m.ceil();
    res = std::all_of(ceil.begin(), ceil.end(), [&](const int &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);
}

TEST(StaticMatrix, sumItems) {
    static_matrix<double, 3, 3> m({1, 2, 3, 1, 2, 3, 1, 2, 3});
    int sum = m.sum();
    ASSERT_EQ(sum, 18);
}

TEST(StaticMatrix, transposematrix) {
    static_matrix<double, 4, 3> m({1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3});
    static_matrix<double, 3, 4> transposed = m.transpose();

    static_matrix<int, 3, 4> correct({1, 4, 7, 1, 2, 5, 8, 2, 3, 6, 9, 3});

    auto begin1 = transposed.begin();
    auto end1 = transposed.end();
    auto begin2 = correct.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(StaticMatrix, minormatrix) {
    static_matrix<int, 3, 3> m({1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 2, 2> minor = m.minor(0, 0);
    ASSERT_EQ(minor.size(), 4);
    ASSERT_EQ(minor.rows(), 2);
    ASSERT_EQ(minor.cols(), 2);

    static_matrix<int, 2, 2> correct({5, 6, 8, 9});
    auto begin1 = minor.begin();
    auto end1 = minor.end();
    auto begin2 = correct.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(StaticMatrix, determinant) {
    static_matrix<int, 3, 3> m({3, 6, 2, 8, 6, 1, 9, 4, 7});
    double determinant1 = m.determinant_gaussian();
    double determinant2 = m.determinant_gaussian();
    ASSERT_DOUBLE_EQ(determinant1, determinant2);
    ASSERT_DOUBLE_EQ(determinant1, -212.0);
    ASSERT_DOUBLE_EQ(determinant2, -212.0);
}

TEST(StaticMatrix, trace) {
    static_matrix<int, 3, 3> m({
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    });

    int trace_correct= 1 + 5 + 9;
    int trace = m.trace();
    ASSERT_EQ(trace, trace_correct);
}

TEST(StaticMatrix, inverse) {
    static_matrix<int, 3, 3> m({2, 5, 0, 0, 9, 7, 8, 1, 3});
    double determinant1 = m.determinant_gaussian();
    double determinant2 = m.determinant_laplacian();
    ASSERT_DOUBLE_EQ(determinant2, determinant1);
    ASSERT_DOUBLE_EQ(determinant2, 320.0);
    ASSERT_DOUBLE_EQ(determinant1, 320.0);

    static_matrix<double, 3, 3> inverse = m.convert_to<double>().inverse();
    static_matrix<double, 3, 3> correct({
            0.0625, -0.046875, 0.109375,
            0.175, 0.01875, -0.04375,
            -0.225, 0.11875, 0.05625
    });

    auto begin1 = inverse.begin();
    auto end1 = inverse.end();
    auto begin2 = correct.begin();

    while (begin1 != end1) {
        ASSERT_DOUBLE_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(StaticMatrix, convestOtherType) {
    static_matrix<int, 3, 3> m({2, 5, 0, 0, 9, 7, 8, 1, 3});
    static_matrix<double, 3, 3> m_double = m.convert_to<double>();

    auto begin1 = m_double.begin();
    auto end1 = m_double.end();
    auto begin2 = m.begin();

    while (begin1 != end1) {
        ASSERT_DOUBLE_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(StaticMatrix, convestToArray) {
    static_matrix<int, 3, 3> m({2, 5, 0, 0, 9, 7, 8, 1, 3});
    std::array<int, 9> arr1 = m.to_array();
    std::array<double, 9> arr2 = m.to_array<double>();

    auto begin1 = m.begin();
    auto end1 = m.end();
    auto begin2 = arr1.begin();
    auto begin3 = arr2.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ASSERT_DOUBLE_EQ(*begin1, *begin3);
        ++begin1, ++begin2, ++begin3;
    }
}

TEST(StaticMatrix, equality) {
    static_matrix<int, 3, 3> m({1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 3, 3> m2 = m;

    auto equal = m2.equal_to(m);
    ASSERT_EQ(equal, true);

    equal = m2 == m;
    ASSERT_EQ(equal, true);
}

TEST(StaticMatrix, join_right) {
    static_matrix<int, 2, 2> matrix1({
        1, 2,
        5, 6
    });

    static_matrix<int, 2, 2> matrix2({
        3, 4,
        7, 8
    });

    static_matrix<int, 2, 4> matrix_correct({
        1, 2, 3, 4,
        5, 6, 7, 8
    });

    static_matrix<int, 2, 4> join_matrix = matrix1.join_right(matrix2);

    auto equal = join_matrix.equal_to(matrix_correct);
    ASSERT_EQ(equal, true);
}

TEST(StaticMatrix, join_left) {
    static_matrix<int, 2, 2> matrix1({
        1, 2,
        5, 6
    });

    static_matrix<int, 2, 2> matrix2({
        3, 4,
        7, 8
    });

    static_matrix<int, 2, 4> matrix_correct({
        3, 4, 1, 2,
        7, 8, 5, 6
    });

    static_matrix<int, 2, 4> join_matrix = matrix1.join_left(matrix2);

    auto equal = join_matrix.equal_to(matrix_correct);
    ASSERT_EQ(equal, true);
}

TEST(StaticMatrix, join_top) {
    static_matrix<int, 2, 2> matrix1({
        5, 6,
        7, 8
    });

    static_matrix<int, 2, 2> matrix2({
        1, 2,
        3, 4
    });

    static_matrix<int, 4, 2> matrix_correct({
        1, 2,
        3, 4,
        5, 6,
        7, 8
    });

    static_matrix<int, 4, 2> join_matrix = matrix1.join_top(matrix2);

    auto equal = join_matrix.equal_to(matrix_correct);
    ASSERT_EQ(equal, true);
}

TEST(StaticMatrix, join_bottom) {
    static_matrix<int, 2, 2> matrix1({
        5, 6,
        7, 8
    });

    static_matrix<int, 2, 2> matrix2({
        1, 2,
        3, 4
    });

    static_matrix<int, 4, 2> matrix_correct({
        5, 6,
        7, 8,
        1, 2,
        3, 4
    });

    static_matrix<int, 4, 2> join_matrix = matrix1.join_bottom(matrix2);

    auto equal = join_matrix.equal_to(matrix_correct);
    ASSERT_EQ(equal, true);
}

TEST(StaticMatrix, swap_rows) {
    static_matrix<int, 3, 3> m({
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    });

    m.swap_rows(0, 1);
    m.swap_rows(1, 2);

    static_matrix<int, 3, 3> correct({
            4, 5, 6,
            7, 8, 9,
            1, 2, 3
    });

    bool equal = m == correct;
    ASSERT_TRUE(equal);
}

TEST(StaticMatrix, swap_cols) {
    static_matrix<int, 3, 3> m({
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
    });

    m.swap_cols(0, 1);
    m.swap_cols(1, 2);

    static_matrix<int, 3, 3> correct({
            4, 7, 1,
            5, 8, 2,
            6, 9, 3
    });

    bool equal = m == correct;
    ASSERT_TRUE(equal);
}