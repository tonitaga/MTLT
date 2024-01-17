#include <gtest/gtest.h>

#include <thread>

#include <mtl/atomic_matrix.h>

using namespace mtl;

TEST(FTAtomicmatrix, Emptymatrix) {
  atomic_matrix<int> m;
  ASSERT_EQ(m.size(), 0);
}

TEST(FTAtomicmatrix, Sizedmatrix) {
  atomic_matrix<int> m(3, 3, 5);
  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(0, 0), 5);
}

TEST(FTAtomicmatrix, Sqmatrix) {
  atomic_matrix<int> m(5);
  ASSERT_EQ(m.size(), 25);
  ASSERT_EQ(m.rows(), 5);
  ASSERT_EQ(m.cols(), 5);
  ASSERT_EQ(m(0, 0), 0);
}

TEST(FTAtomicmatrix, InitializerList) {
  atomic_matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(0, 0), 1);
}

TEST(FTAtomicmatrix, ContainerConstructor) {
  atomic_matrix<int> m(3, 3, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(0, 0), 1);
}

TEST(FTAtomicmatrix, IdentityStaticMethod) {
  atomic_matrix<int> m = atomic_matrix<int>::identity(3, 3);
  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(2, 2), 1);
}

TEST(FTAtomicmatrix, CopyConstructor) {
  atomic_matrix<int> m = atomic_matrix<int>::identity(3, 3);
  atomic_matrix<int> m2 = m;
  ASSERT_EQ(m2.size(), 9);
  ASSERT_EQ(m2.rows(), 3);
  ASSERT_EQ(m2.cols(), 3);
  ASSERT_EQ(m2(2, 2), 1);
}

TEST(FTAtomicmatrix, CopyAssignment) {
  atomic_matrix<int> m = atomic_matrix<int>::identity(3, 3);
  atomic_matrix<int> m2;
  m2 = m;
  ASSERT_EQ(m2.size(), 9);
  ASSERT_EQ(m2.rows(), 3);
  ASSERT_EQ(m2.cols(), 3);
  ASSERT_EQ(m2(2, 2), 1);
}

TEST(FTAtomicmatrix, MoveConstructor) {
  atomic_matrix<int> m = atomic_matrix<int>::identity(3, 3);
  atomic_matrix<int> m2 = std::move(m);
  ASSERT_EQ(m2.size(), 9);
  ASSERT_EQ(m2.rows(), 3);
  ASSERT_EQ(m2.cols(), 3);
  ASSERT_EQ(m2(2, 2), 1);
  ASSERT_EQ(m.size(), 0);
  ASSERT_EQ(m.rows(), 0);
  ASSERT_EQ(m.cols(), 0);
  EXPECT_THROW(m.at(0, 0), std::out_of_range);
}

TEST(FTAtomicmatrix, ChangeSizes) {
  atomic_matrix<int> m(3, 3, 1);
  m.rows(5);
  m.cols(5);
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

TEST(FTAtomicmatrix, transformUnary) {
  atomic_matrix<int> m(3, 3, 1);
  m.transform([](const int &item) { return item * 2; });
  ASSERT_EQ(m(0, 0), 2);
}

TEST(FTAtomicmatrix, transformBinary) {
  atomic_matrix<int> m1(3, 3, 1);
  atomic_matrix<int> m2(3, 3, 2);
  m1.transform(m2, [](const std::atomic<int> &lhs, const std::atomic<int> &rhs) { return lhs + rhs; });
  ASSERT_EQ(m1(0, 0), 3);
}

TEST(FTAtomicmatrix, generate) {
  auto zero_operation = [] { return 0; };

  atomic_matrix<int> m(3, 3, 1);
  m.generate(zero_operation);
  ASSERT_EQ(m(0, 0), 0);
}

TEST(FTAtomicmatrix, mathOperationsNumber) {
  atomic_matrix<int> m(3, 3, 10);
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

TEST(FTAtomicmatrix, mulmatrix) {
  atomic_matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  atomic_matrix<int> m2(3, 3, {9, 8, 7, 6, 5, 4, 3, 2, 1});
  atomic_matrix<int> m3 = m1.mul(m2);
  atomic_matrix<int> m4(3, 3, {30, 24, 18, 84, 69, 54, 138, 114, 90});

  auto begin1 = m3.begin();
  auto end1 = m3.end();
  auto begin2 = m4.begin();

  while (begin1 != end1) {
	ASSERT_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(FTAtomicmatrix, fillRandom) {
  atomic_matrix<int> m(3, 3);
  m.fill_random(5, 5);
  ASSERT_EQ(m(0, 2), 5);
}

TEST(FTAtomicmatrix, roundItems) {
  atomic_matrix<double> m(3, 3, 1.9);
  m.to_round();
  auto res = std::all_of(m.begin(), m.end(), [&](const double &item) {
	return item == 2.0;
  });

  ASSERT_EQ(res, true);
  m = atomic_matrix<double>(3, 3, 1.9);
  atomic_matrix<double> round = m.round();
  res = std::all_of(round.begin(), round.end(), [&](const double &item) {
	return item == 2.0;
  });

  ASSERT_EQ(res, true);
}

TEST(FTAtomicmatrix, floorItems) {
  atomic_matrix<double> m(3, 3, 1.9);
  m.to_floor();
  auto res = std::all_of(m.begin(), m.end(), [&](const double &item) {
	return item == 1.0;
  });

  ASSERT_EQ(res, true);
  m = atomic_matrix<double>(3, 3, 1.9);
  atomic_matrix<double> floor = m.floor();
  res = std::all_of(floor.begin(), floor.end(), [&](const double &item) {
	return item == 1.0;
  });

  ASSERT_EQ(res, true);
}

TEST(FTAtomicmatrix, ceilItems) {
  atomic_matrix<double> m(3, 3, 1.001);
  m.to_ceil();
  auto res = std::all_of(m.begin(), m.end(), [&](const double &item) {
	return item == 2.0;
  });

  ASSERT_EQ(res, true);
  m = atomic_matrix<double>(3, 3, 1.001);
  atomic_matrix<double> ceil = m.ceil();
  res = std::all_of(ceil.begin(), ceil.end(), [&](const double &item) {
	return item == 2.0;
  });

  ASSERT_EQ(res, true);
}

TEST(FTAtomicmatrix, sumItems) {
  atomic_matrix<int> m(3, 3, {1, 2, 3, 1, 2, 3, 1, 2, 3});
  int sum = m.sum();
  ASSERT_EQ(sum, 18);
}

TEST(FTAtomicmatrix, transposematrix) {
  atomic_matrix<int> m(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3});
  atomic_matrix<int> transposed = m.transpose();

  atomic_matrix<int> correct(3, 4, {1, 4, 7, 1, 2, 5, 8, 2, 3, 6, 9, 3});
  auto begin1 = transposed.begin();
  auto end1 = transposed.end();
  auto begin2 = correct.begin();

  while (begin1 != end1) {
	ASSERT_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(FTAtomicmatrix, minormatrix) {
  atomic_matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  atomic_matrix<int> minor = m.minor(0, 0);
  ASSERT_EQ(minor.size(), 4);
  ASSERT_EQ(minor.rows(), 2);
  ASSERT_EQ(minor.cols(), 2);

  atomic_matrix<int> correct(2, 2, {5, 6, 8, 9});
  auto begin1 = minor.begin();
  auto end1 = minor.end();
  auto begin2 = correct.begin();

  while (begin1 != end1) {
	ASSERT_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(FTAtomicmatrix, determinant) {
  atomic_matrix<int> m(3, 3, {3, 6, 2, 8, 6, 1, 9, 4, 7});
  double determinant1 = m.determinant_gaussian();
  double determinant2 = m.determinant_laplacian();
  ASSERT_DOUBLE_EQ(determinant1, determinant2);
  ASSERT_DOUBLE_EQ(determinant1, -212.0);
  ASSERT_DOUBLE_EQ(determinant2, -212.0);
  m.resize(3, 4);
  EXPECT_THROW(m.determinant_gaussian(), std::logic_error);
}

TEST(FTAtomicmatrix, trace) {
  atomic_matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  int trace_correct = 1 + 5 + 9;
  int trace = m.trace();
  ASSERT_EQ(trace, trace_correct);

  m.resize(3, 4);
  EXPECT_THROW(m.trace(), std::logic_error);
}

TEST(FTAtomicmatrix, inverse) {
  atomic_matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
  double determinant = m.determinant_gaussian();
  ASSERT_DOUBLE_EQ(determinant, 320.0);

  atomic_matrix<double> inverse = m.convert_to<double>().inverse();
  atomic_matrix<double> correct(3, 3, {
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

  m = atomic_matrix<int>(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_THROW(m.inverse(), std::logic_error);
}

TEST(FTAtomicmatrix, convestOtherType) {
  atomic_matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
  atomic_matrix<double> m_double = m.convert_to<double>();

  auto begin1 = m_double.begin();
  auto end1 = m_double.end();
  auto begin2 = m.begin();

  while (begin1 != end1) {
	ASSERT_DOUBLE_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(FTAtomicmatrix, convestToVector) {
  atomic_matrix<int> m(3, 3, {2, 5, 0, 0, 9, 7, 8, 1, 3});
  std::vector<std::atomic<int>> vec = m.to_vector();

  auto begin1 = m.begin();
  auto end1 = m.end();
  auto begin2 = vec.begin();

  while (begin1 != end1) {
	ASSERT_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(FTAtomicmatrix, equality) {
  atomic_matrix<int> m(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  atomic_matrix<int> m2 = m;

  auto equal = m2.equal_to(m);
  ASSERT_EQ(equal, true);

  equal = m2 == m;
  ASSERT_EQ(equal, true);
}

TEST(FTAtomicmatrix, to_join_right) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  m.to_join_right(m2);
  atomic_matrix<int> m_correct(2, 4, {
	  1, 2, 3, 4,
	  5, 6, 7, 8
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(FTAtomicmatrix, join_right) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  auto join = m.join_right(m2);
  atomic_matrix<int> m_correct(2, 4, {
	  1, 2, 3, 4,
	  5, 6, 7, 8
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(FTAtomicmatrix, to_join_left) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  m.to_join_left(m2);
  atomic_matrix<int> m_correct(2, 4, {
	  3, 4, 1, 2,
	  7, 8, 5, 6
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(FTAtomicmatrix, join_left) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  auto join = m.join_left(m2);
  atomic_matrix<int> m_correct(2, 4, {
	  3, 4, 1, 2,
	  7, 8, 5, 6
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(FTAtomicmatrix, to_join_top) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  m.to_join_top(m2);
  atomic_matrix<int> m_correct(4, 2, {
	  3, 4,
	  7, 8,
	  1, 2,
	  5, 6
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(FTAtomicmatrix, join_top) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  auto join = m.join_top(m2);
  atomic_matrix<int> m_correct(4, 2, {
	  3, 4,
	  7, 8,
	  1, 2,
	  5, 6
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(FTAtomicmatrix, to_join_bottom) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  m.to_join_bottom(m2);
  atomic_matrix<int> m_correct(4, 2, {
	  1, 2,
	  5, 6,
	  3, 4,
	  7, 8
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(FTAtomicmatrix, join_bottom) {
  atomic_matrix<int> m(2, 2, {
	  1, 2,
	  5, 6
  });

  atomic_matrix<int> m2(2, 2, {
	  3, 4,
	  7, 8
  });

  auto join = m.join_bottom(m2);
  atomic_matrix<int> m_correct(4, 2, {
	  1, 2,
	  5, 6,
	  3, 4,
	  7, 8
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(FTAtomicmatrix, swap_rows) {
  atomic_matrix<int> m(3, 3, {
	  1, 2, 3,
	  4, 5, 6,
	  7, 8, 9
  });

  m.swap_rows(0, 1);
  m.swap_rows(1, 2);

  atomic_matrix<int> correct(3, 3, {
	  4, 5, 6,
	  7, 8, 9,
	  1, 2, 3
  });

  bool equal = m == correct;
  ASSERT_TRUE(equal);
}

TEST(FTAtomicmatrix, swap_cols) {
  atomic_matrix<int> m(3, 3, {
	  1, 4, 7,
	  2, 5, 8,
	  3, 6, 9
  });

  m.swap_cols(0, 1);
  m.swap_cols(1, 2);

  atomic_matrix<int> correct(3, 3, {
	  4, 7, 1,
	  5, 8, 2,
	  6, 9, 3
  });

  bool equal = m == correct;
  ASSERT_TRUE(equal);
}

TEST(FTAtomicmatrix, ThreadsValueChange) {
  atomic_matrix<int> matrix(3, 3);

  std::vector<std::thread> threads;
  threads.reserve(10);

  for (std::size_t i = 0; i != 10; i++) {
	threads.emplace_back([&matrix] {
	  for (int i = 0; i != 10000; i++) {
		for (auto &value : matrix) {
		  value.fetch_add(1);
		}
	  }
	});
  }

  for (auto &thread : threads)
	if (thread.joinable())
	  thread.join();


  atomic_matrix<int> correct(3, 3, 100000);

  ASSERT_TRUE(correct.equal_to(matrix));
}
