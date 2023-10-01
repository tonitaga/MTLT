#include <gtest/gtest.h>

#include "matrix"
#include "static_matrix"

using namespace ng;

TEST(DynamicMatrix, EmptyMatrix) {
    Matrix<int> m;
    ASSERT_EQ(m.size(), 0);
}

TEST(DynamicMatrix, SizedMatrix) {
    Matrix<int> m(3, 3, 5);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 5);
}

TEST(DynamicMatrix, SqMatrix) {
    Matrix<int> m(5);
    ASSERT_EQ(m.size(), 25);
    ASSERT_EQ(m.rows(), 5);
    ASSERT_EQ(m.cols(), 5);
    ASSERT_EQ(m(0, 0), 0);
}

TEST(DynamicMatrix, MatrixVector) {
    std::vector<std::vector<int>> v {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    Matrix<int> m(v);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(DynamicMatrix, InitializerList) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(DynamicMatrix, ContainerConstructor) {
    Matrix<int> m(3, 3, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(DynamicMatrix, IdentityStaticMethod) {
    Matrix m = Matrix<int>::identity(3, 3);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(2, 2), 1);
}

TEST(DynamicMatrix, CopyConstructor) {
    Matrix m = Matrix<int>::identity(3, 3);
    Matrix m2 = m;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
}

TEST(DynamicMatrix, CopyAssignment) {
    Matrix m = Matrix<int>::identity(3, 3);
    Matrix<int> m2;
    m2 = m;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
}

TEST(DynamicMatrix, MoveConstructor) {
    Matrix m = Matrix<int>::identity(3, 3);
    Matrix<int> m2 = std::move(m);
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
    ASSERT_EQ(m.size(), 0);
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
    EXPECT_THROW(m.at(0, 0), std::out_of_range);
}

TEST(DynamicMatrix, IterationBegin) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto begin = m.begin(); begin += 2;
    auto cbegin = m.cbegin();
    auto rbegin = m.rbegin(); rbegin += 1;
    auto crbegin = m.crbegin();
    ASSERT_EQ(*begin, 3);
    ASSERT_EQ(*cbegin, 1);
    ASSERT_EQ(*rbegin, 8);
    ASSERT_EQ(*crbegin, 9);
}

TEST(DynamicMatrix, IterationEnd) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto end = m.end(); end -= 2;
    auto cend = m.cend(); cend -= 1;
    auto rend = m.rend(); rend -= 1;
    auto crend = m.crend(); crend -= 2;
    ASSERT_EQ(*end, 8);
    ASSERT_EQ(*cend, 9);
    ASSERT_EQ(*rend, 1);
    ASSERT_EQ(*crend, 2);
}

TEST(DynamicMatrix, ChangeSizes) {
    Matrix<int> m(3, 3, 1);
    m.rows(5); m.cols(5);
    ASSERT_EQ(m.rows(), 5);
    ASSERT_EQ(m.cols(), 5);
    ASSERT_EQ(m(4, 4), 0);

    m.resize(3, 3);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(2, 2), 1);

    m.clear();
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
    EXPECT_THROW(m.at(0, 0), std::out_of_range);
}

TEST(DynamicMatrix, transformUnary) {
    Matrix<int> m(3, 3, 1);
    m.transform([](const auto &item) { return item * 2; });
    ASSERT_EQ(m(0, 0), 2);
}

TEST(DynamicMatrix, transformBinary) {
    Matrix<int> m1(3, 3, 1);
    Matrix<int> m2(3, 3, 2);
    m1.transform(m2, [](const auto &lhs, const auto &rhs) { return lhs + rhs; });
    ASSERT_EQ(m1(0, 0), 3);
}

TEST(DynamicMatrix, generate) {
    auto zero_operation = []{ return 0; };

    Matrix<int> m(3, 3, 1);
    m.generate(zero_operation);
    ASSERT_EQ(m(0, 0), 0);
}

TEST(DynamicMatrix, mathOperationsNumber) {
    Matrix<int> m(3, 3, 10);
    m.mul(2);
    ASSERT_EQ(m(1, 1), 20);
    m.div(2);
    ASSERT_EQ(m(2, 0), 10);
    m.add(5);
    ASSERT_EQ(m(1, 2), 15);
    m.sub(5);
    ASSERT_EQ(m(0, 2), 10);
    m *= 2;
    ASSERT_EQ(m(1, 1), 20);
    m /= 2;
    ASSERT_EQ(m(2, 0), 10);
    m += 5;
    ASSERT_EQ(m(1, 2), 15);
    m -= 5;
    ASSERT_EQ(m(0, 2), 10);
}

TEST(DynamicMatrix, mulMatrix) {
    Matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix<int> m2(3, 3, {9, 8, 7, 6, 5, 4, 3, 2, 1});
    Matrix<int> m3 = m1.mul(m2);
    Matrix<int> m4(3, 3, {30, 24, 18, 84, 69, 54, 138, 114, 90});

    auto begin1 = m3.begin();
    auto end1 = m3.end();
    auto begin2 = m4.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(DynamicMatrix, fillRandom) {
    Matrix<int> m(3, 3);
    m.fill_random(5, 5);
    ASSERT_EQ(m(0, 2), 5);
}

TEST(DynamicMatrix, roundItems) {
    Matrix<double> m(3, 3, 1.9);
    m.round();
    auto res = std::all_of(m.begin(), m.end(), [&](const auto &item) {
        return item == 2.0;
    });
    ASSERT_EQ(res, true);
}

TEST(DynamicMatrix, floorItems) {
    Matrix<double> m(3, 3, 1.9);
    m.floor();
    auto res = std::all_of(m.begin(), m.end(), [&](const auto &item) {
        return item == 1.0;
    });
    ASSERT_EQ(res, true);
}

TEST(DynamicMatrix, ceilItems) {
    Matrix<double> m(3, 3, 1.001);
    m.ceil();
    auto res = std::all_of(m.begin(), m.end(), [&](const auto &item) {
        return item == 2.0;
    });
    ASSERT_EQ(res, true);
}

TEST(DynamicMatrix, sumItems) {
    Matrix<int> m(3, 3, {1, 2, 3, 1, 2, 3, 1, 2, 3});
    int sum = m.sum();
    ASSERT_EQ(sum, 18);
}

TEST(DynamicMatrix, transposeMatrix) {
    Matrix<int> m(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3});
    Matrix<int> transposed = m.transpose();

    Matrix<int> correct(3, 4, {1, 4, 7, 1, 2, 5, 8, 2, 3, 6, 9, 3});
    auto begin1 = transposed.begin();
    auto end1 = transposed.end();
    auto begin2 = correct.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(DynamicMatrix, minorMatrix) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix<int> minor = m.minor(0, 0);
    ASSERT_EQ(minor.size(), 4);
    ASSERT_EQ(minor.rows(), 2);
    ASSERT_EQ(minor.cols(), 2);

    Matrix<int> correct(2, 2, {5, 6, 8, 9});
    auto begin1 = minor.begin();
    auto end1 = minor.end();
    auto begin2 = correct.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(DynamicMatrix, determinant) {
    Matrix<int> m(3, 3, {3, 6, 2, 8, 6, 1, 9, 4, 7});
    int determinant = m.determinant();
    ASSERT_EQ(determinant, -212);

    m.resize(3, 4);
    EXPECT_THROW(m.determinant(), std::logic_error);
}

TEST(DynamicMatrix, trace) {
    Matrix<int> m(3, 3, {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    });

    int trace_correct= 1 + 5 + 9;
    int trace = m.trace();
    ASSERT_EQ(trace, trace_correct);

    m.resize(3, 4);
    EXPECT_THROW(m.trace(), std::logic_error);
}

TEST(DynamicMatrix, inverse) {
    Matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    int determinant = m.determinant();
    ASSERT_EQ(determinant, 320);

    Matrix<double> inverse = m.convert_to<double>().inverse();
    Matrix<double> correct(3, 3, {
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

    m = Matrix<int>(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    EXPECT_THROW(m.inverse(), std::logic_error);
}

TEST(DynamicMatrix, convestOtherType) {
    Matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    Matrix<double> m_double = m.convert_to<double>();

    auto begin1 = m_double.begin();
    auto end1 = m_double.end();
    auto begin2 = m.begin();

    while (begin1 != end1) {
        ASSERT_DOUBLE_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(DynamicMatrix, convestToVector) {
    Matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    std::vector vec = m.convert_to_vector();

    auto begin1 = m.begin();
    auto end1 = m.end();
    auto begin2 = vec.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(DynamicMatrix, convestToMatrixVector) {
    Matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    std::vector<std::vector<int>> vec = m.convert_to_matrix_vector();

    for (size_t row = 0; row != m.rows(); ++row)
        for (size_t col = 0; col != m.cols(); ++col)
            ASSERT_EQ(m(row, col), vec[row][col]);
}

TEST(DynamicMatrix, equality) {
    Matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix<int> m2 = m;

    auto equal = m2.equal_to(m);
    ASSERT_EQ(equal, true);

    equal = m2 == m;
    ASSERT_EQ(equal, true);
}
