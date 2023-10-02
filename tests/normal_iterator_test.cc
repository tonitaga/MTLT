#include "matrix.h"
#include "static_matrix.h"

#include <gtest/gtest.h>

using namespace mtl;

TEST(NormalIterator, begin_matrix) {
    matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    const matrix<int> m2(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    auto begin1 = m1.begin();
    auto const_begin1 = m1.cbegin();

    auto begin2 = m2.begin();
    auto const_begin2 = m2.cbegin();

    ASSERT_EQ(*begin1, 1);
    ASSERT_EQ(*begin2, 1);

    ASSERT_EQ(*(begin1 + 2), 3);
    ASSERT_EQ(*(begin2 + 2), 3);

    ASSERT_EQ(*(++begin1), 2);
    ASSERT_EQ(*(++begin2), 2);
}

TEST(NormalIterator, begin_static_matrix) {
    static_matrix<int, 3, 3> m1({1, 2, 3, 4, 5, 6, 7, 8, 9});
    const static_matrix<int, 3, 3> m2({1, 2, 3, 4, 5, 6, 7, 8, 9});

    auto begin1 = m1.begin();
    auto const_begin1 = m1.cbegin();

    auto begin2 = m2.begin();
    auto const_begin2 = m2.cbegin();

    ASSERT_EQ(*begin1, 1);
    ASSERT_EQ(*begin2, 1);

    ASSERT_EQ(*(begin1 + 2), 3);
    ASSERT_EQ(*(begin2 + 2), 3);

    ASSERT_EQ(*(++begin1), 2);
    ASSERT_EQ(*(++begin2), 2);
}

TEST(NormalIterator, iter_tag) {
    bool is_same1 = std::is_same<static_matrix<int, 1, 1>::iterator::iterator_category, std::random_access_iterator_tag>::value;
    bool is_same2 = std::is_same<matrix<int>::iterator::iterator_category, std::random_access_iterator_tag>::value;

    ASSERT_TRUE(is_same1);
    ASSERT_TRUE(is_same2);
}

TEST(NormalIterator, distance) {
    matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 3, 3> m2({1, 2, 3, 4, 5, 6, 7, 8, 9});

    auto begin1 = m1.begin(), end1 = m1.end();
    auto begin2 = m2.begin(), end2 = m2.end();

    ASSERT_EQ(std::distance(begin1, end1), 9);
    ASSERT_EQ(std::distance(begin2, end2), 9);
}

TEST(NormalIterator, container_creation) {
    matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    static_matrix<int, 3, 3> m2({1, 2, 3, 4, 5, 6, 7, 8, 9});

    std::vector<int> vec1(m1.begin(), m1.end());
    std::vector<int> vec2(m2.begin(), m2.end());

    auto begin_m1 = m1.begin();
    auto begin_m2 = m2.begin();
    auto begin_vec1 = vec1.begin();
    auto begin_vec2 = vec2.begin();

    auto end_m1 = m1.end();

    while (begin_m1 != end_m1) {
        ASSERT_EQ(*begin_m1, *begin_vec1);
        ASSERT_EQ(*begin_m2, *begin_vec2);

        ++begin_m1, ++begin_m2, ++begin_vec1, ++begin_vec2;
    }
}