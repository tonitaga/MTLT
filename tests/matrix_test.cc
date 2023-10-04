#include <gtest/gtest.h>

#include "matrix.h"

using namespace mtl;

TEST(Dynamicmatrix, Emptymatrix) {
    matrix<int> m;
    ASSERT_EQ(m.size(), 0);
}

TEST(Dynamicmatrix, Sizedmatrix) {
    matrix<int> m(3, 3, 5);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 5);
}

TEST(Dynamicmatrix, Sqmatrix) {
    matrix<int> m(5);
    ASSERT_EQ(m.size(), 25);
    ASSERT_EQ(m.rows(), 5);
    ASSERT_EQ(m.cols(), 5);
    ASSERT_EQ(m(0, 0), 0);
}

TEST(Dynamicmatrix, matrixVector) {
    std::vector<std::vector<int>> v {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    matrix<int> m(v);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(Dynamicmatrix, InitializerList) {
    matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(Dynamicmatrix, ContainerConstructor) {
    matrix<int> m(3, 3, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(0, 0), 1);
}

TEST(Dynamicmatrix, IdentityStaticMethod) {
    matrix<int> m = matrix<int>::identity(3, 3);
    ASSERT_EQ(m.size(), 9);
    ASSERT_EQ(m.rows(), 3);
    ASSERT_EQ(m.cols(), 3);
    ASSERT_EQ(m(2, 2), 1);
}

TEST(Dynamicmatrix, CopyConstructor) {
    matrix<int> m = matrix<int>::identity(3, 3);
    matrix<int> m2 = m;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
}

TEST(Dynamicmatrix, CopyAssignment) {
    matrix<int> m = matrix<int>::identity(3, 3);
    matrix<int> m2;
    m2 = m;
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
}

TEST(Dynamicmatrix, MoveConstructor) {
    matrix<int> m = matrix<int>::identity(3, 3);
    matrix<int> m2 = std::move(m);
    ASSERT_EQ(m2.size(), 9);
    ASSERT_EQ(m2.rows(), 3);
    ASSERT_EQ(m2.cols(), 3);
    ASSERT_EQ(m2(2, 2), 1);
    ASSERT_EQ(m.size(), 0);
    ASSERT_EQ(m.rows(), 0);
    ASSERT_EQ(m.cols(), 0);
    EXPECT_THROW(m.at(0, 0), std::out_of_range);
}

TEST(Dynamicmatrix, ChangeSizes) {
    matrix<int> m(3, 3, 1);
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

TEST(Dynamicmatrix, transformUnary) {
    matrix<int> m(3, 3, 1);
    m.transform([](const int &item) { return item * 2; });
    ASSERT_EQ(m(0, 0), 2);
}

TEST(Dynamicmatrix, transformBinary) {
    matrix<int> m1(3, 3, 1);
    matrix<int> m2(3, 3, 2);
    m1.transform(m2, [](const int &lhs, const int &rhs) { return lhs + rhs; });
    ASSERT_EQ(m1(0, 0), 3);
}

TEST(Dynamicmatrix, generate) {
    auto zero_operation = []{ return 0; };

    matrix<int> m(3, 3, 1);
    m.generate(zero_operation);
    ASSERT_EQ(m(0, 0), 0);
}

TEST(Dynamicmatrix, mathOperationsNumber) {
    matrix<int> m(3, 3, 10);
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

TEST(Dynamicmatrix, mulmatrix) {
    matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix<int> m2(3, 3, {9, 8, 7, 6, 5, 4, 3, 2, 1});
    matrix<int> m3 = m1.mul(m2);
    matrix<int> m4(3, 3, {30, 24, 18, 84, 69, 54, 138, 114, 90});

    auto begin1 = m3.begin();
    auto end1 = m3.end();
    auto begin2 = m4.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(Dynamicmatrix, fillRandom) {
    matrix<int> m(3, 3);
    m.fill_random(5, 5);
    ASSERT_EQ(m(0, 2), 5);
}

TEST(Dynamicmatrix, roundItems) {
    matrix<double> m(3, 3, 1.9);
    m.to_round();
    auto res = std::all_of(m.begin(), m.end(), [&](const double &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);
    m = matrix<double>(3, 3, 1.9);
    matrix<double> round = m.round();
    res = std::all_of(round.begin(), round.end(), [&](const double &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);
}

TEST(Dynamicmatrix, floorItems) {
    matrix<double> m(3, 3, 1.9);
    m.to_floor();
    auto res = std::all_of(m.begin(), m.end(), [&](const double &item) {
        return item == 1.0;
    });

    ASSERT_EQ(res, true);
    m = matrix<double>(3, 3, 1.9);
    matrix<double> floor = m.floor();
    res = std::all_of(floor.begin(), floor.end(), [&](const double &item) {
        return item == 1.0;
    });

    ASSERT_EQ(res, true);
}

TEST(Dynamicmatrix, ceilItems) {
    matrix<double> m(3, 3, 1.001);
    m.to_ceil();
    auto res = std::all_of(m.begin(), m.end(), [&](const double &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);
    m = matrix<double>(3, 3, 1.001);
    matrix<double> ceil = m.ceil();
    res = std::all_of(ceil.begin(), ceil.end(), [&](const double &item) {
        return item == 2.0;
    });

    ASSERT_EQ(res, true);
}

TEST(Dynamicmatrix, sumItems) {
    matrix<int> m(3, 3, {1, 2, 3, 1, 2, 3, 1, 2, 3});
    int sum = m.sum();
    ASSERT_EQ(sum, 18);
}

TEST(Dynamicmatrix, transposematrix) {
    matrix<int> m(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3});
    matrix<int> transposed = m.transpose();

    matrix<int> correct(3, 4, {1, 4, 7, 1, 2, 5, 8, 2, 3, 6, 9, 3});
    auto begin1 = transposed.begin();
    auto end1 = transposed.end();
    auto begin2 = correct.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(Dynamicmatrix, minormatrix) {
    matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix<int> minor = m.minor(0, 0);
    ASSERT_EQ(minor.size(), 4);
    ASSERT_EQ(minor.rows(), 2);
    ASSERT_EQ(minor.cols(), 2);

    matrix<int> correct(2, 2, {5, 6, 8, 9});
    auto begin1 = minor.begin();
    auto end1 = minor.end();
    auto begin2 = correct.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(Dynamicmatrix, determinant) {
    matrix<int> m(3, 3, {3, 6, 2, 8, 6, 1, 9, 4, 7});
    double determinant1 = m.determinant_gaussian();
    double determinant2 = m.determinant_laplacian();
    ASSERT_DOUBLE_EQ(determinant1, determinant2);
    ASSERT_DOUBLE_EQ(determinant1, -212.0);
    ASSERT_DOUBLE_EQ(determinant2, -212.0);
    m.resize(3, 4);
    EXPECT_THROW(m.determinant_gaussian(), std::logic_error);
}

TEST(Dynamicmatrix, trace) {
    matrix<int> m(3, 3, {
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

TEST(Dynamicmatrix, inverse) {
    matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    double determinant = m.determinant_gaussian();
    ASSERT_DOUBLE_EQ(determinant, 320.0);

    matrix<double> inverse = m.convert_to<double>().inverse();
    matrix<double> correct(3, 3, {
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

    m = matrix<int>(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    EXPECT_THROW(m.inverse(), std::logic_error);
}

TEST(Dynamicmatrix, convestOtherType) {
    matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    matrix<double> m_double = m.convert_to<double>();

    auto begin1 = m_double.begin();
    auto end1 = m_double.end();
    auto begin2 = m.begin();

    while (begin1 != end1) {
        ASSERT_DOUBLE_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(Dynamicmatrix, convestToVector) {
    matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    std::vector<int> vec = m.to_vector();

    auto begin1 = m.begin();
    auto end1 = m.end();
    auto begin2 = vec.begin();

    while (begin1 != end1) {
        ASSERT_EQ(*begin1, *begin2);
        ++begin1, ++begin2;
    }
}

TEST(Dynamicmatrix, convestTomatrixVector) {
    matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
    std::vector<std::vector<int>> vec = m.to_matrix_vector();

    for (size_t row = 0; row != m.rows(); ++row)
        for (size_t col = 0; col != m.cols(); ++col)
            ASSERT_EQ(m(row, col), vec[row][col]);
}

TEST(Dynamicmatrix, equality) {
    matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix<int> m2 = m;

    auto equal = m2.equal_to(m);
    ASSERT_EQ(equal, true);

    equal = m2 == m;
    ASSERT_EQ(equal, true);
}

TEST(Dynamicmatrix, to_join_right) {
    matrix<int> m(2, 2, {
        1, 2,
        5, 6
    });

    matrix<int> m2(2, 2, {
        3, 4,
        7, 8
    });

    m.to_join_right(m2);
    matrix<int> m_correct(2, 4, {
        1, 2, 3, 4,
        5, 6, 7, 8
    });

    ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(Dynamicmatrix, join_right) {
    matrix<int> m(2, 2, {
            1, 2,
            5, 6
    });

    matrix<int> m2(2, 2, {
            3, 4,
            7, 8
    });

    auto join = m.join_right(m2);
    matrix<int> m_correct(2, 4, {
            1, 2, 3, 4,
            5, 6, 7, 8
    });

    ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(Dynamicmatrix, to_join_left) {
    matrix<int> m(2, 2, {
            1, 2,
            5, 6
    });

    matrix<int> m2(2, 2, {
            3, 4,
            7, 8
    });

    m.to_join_left(m2);
    matrix<int> m_correct(2, 4, {
            3, 4, 1, 2,
            7, 8, 5, 6
    });

    ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(Dynamicmatrix, join_left) {
    matrix<int> m(2, 2, {
            1, 2,
            5, 6
    });

    matrix<int> m2(2, 2, {
            3, 4,
            7, 8
    });

    auto join = m.join_left(m2);
    matrix<int> m_correct(2, 4, {
            3, 4, 1, 2,
            7, 8, 5, 6
    });

    ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(Dynamicmatrix, to_join_top) {
    matrix<int> m(2, 2, {
            1, 2,
            5, 6
    });

    matrix<int> m2(2, 2, {
            3, 4,
            7, 8
    });

    m.to_join_top(m2);
    matrix<int> m_correct(4, 2, {
            3, 4,
            7, 8,
            1, 2,
            5, 6
    });

    ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(Dynamicmatrix, join_top) {
    matrix<int> m(2, 2, {
            1, 2,
            5, 6
    });

    matrix<int> m2(2, 2, {
            3, 4,
            7, 8
    });

    auto join = m.join_top(m2);
    matrix<int> m_correct(4, 2, {
            3, 4,
            7, 8,
            1, 2,
            5, 6
    });

    ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(Dynamicmatrix, to_join_bottom) {
    matrix<int> m(2, 2, {
            1, 2,
            5, 6
    });

    matrix<int> m2(2, 2, {
            3, 4,
            7, 8
    });

    m.to_join_bottom(m2);
    matrix<int> m_correct(4, 2, {
            1, 2,
            5, 6,
            3, 4,
            7, 8
    });

    ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(Dynamicmatrix, join_bottom) {
    matrix<int> m(2, 2, {
            1, 2,
            5, 6
    });

    matrix<int> m2(2, 2, {
            3, 4,
            7, 8
    });

    auto join = m.join_bottom(m2);
    matrix<int> m_correct(4, 2, {
            1, 2,
            5, 6,
            3, 4,
            7, 8
    });

    ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(Dynamicmatrix, swap_rows) {
    matrix<int> m(3, 3, {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    });

    m.swap_rows(0, 1);
    m.swap_rows(1, 2);

    matrix<int> correct(3, 3, {
            4, 5, 6,
            7, 8, 9,
            1, 2, 3
    });

    bool equal = m == correct;
    ASSERT_TRUE(equal);
}

TEST(Dynamicmatrix, swap_cols) {
    matrix<int> m(3, 3, {
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
    });

    m.swap_cols(0, 1);
    m.swap_cols(1, 2);

    matrix<int> correct(3, 3, {
            4, 7, 1,
            5, 8, 2,
            6, 9, 3
    });

    bool equal = m == correct;
    ASSERT_TRUE(equal);
}