#include <gtest/gtest.h>

#include <mtlt/matrix.h>

using namespace mtlt;

TEST(NFTDynamicmatrix, Emptymatrix) {
  matrix<std::string> m;
  ASSERT_EQ(m.size(), 0);
}

TEST(NFTDynamicmatrix, Sizedmatrix) {
  matrix<std::string> m(3, 3, "Hello MTL");
  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(0, 0), "Hello MTL");
}

TEST(NFTDynamicmatrix, Sqmatrix) {
  matrix<std::string> m(5);
  ASSERT_EQ(m.size(), 25);
  ASSERT_EQ(m.rows(), 5);
  ASSERT_EQ(m.cols(), 5);
  ASSERT_EQ(m(0, 0), "");
}

TEST(NFTDynamicmatrix, matrixVector) {
  std::vector<std::vector<std::string>> v(3, std::vector<std::string>(3));
  matrix<std::string> m(v);
  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(0, 0), "");
}

TEST(NFTDynamicmatrix, InitializerList) {
  matrix<std::string> m(3, 3, {
	"1", "2", "3",
	"4", "5", "6",
	"7", "8", "9"
  });

  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(0, 0), "1");
}

TEST(NFTDynamicmatrix, ContainerConstructor) {
  std::vector<std::string> vec {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9"
  };

  matrix<std::string> m(3, 3, vec);
  ASSERT_EQ(m.size(), 9);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(0, 0), "1");
}

TEST(NFTDynamicmatrix, CopyConstructor) {
  std::vector<std::string> vec {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9"
  };

  matrix<std::string> m(3, 3, vec);
  matrix<std::string> m2 = m;

  ASSERT_EQ(m2.size(), 9);
  ASSERT_EQ(m2.rows(), 3);
  ASSERT_EQ(m2.cols(), 3);
  ASSERT_EQ(m2(2, 2), "9");
}

TEST(NFTDynamicmatrix, CopyAssignment) {
  std::vector<std::string> vec {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9"
  };

  matrix<std::string> m(3, 3, vec);
  matrix<std::string> m2;
  m2 = m;

  ASSERT_EQ(m2.size(), 9);
  ASSERT_EQ(m2.rows(), 3);
  ASSERT_EQ(m2.cols(), 3);
  ASSERT_EQ(m2(2, 2), "9");
}

TEST(NFTDynamicmatrix, MoveConstructor) {
  std::vector<std::string> vec {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9"
  };

  matrix<std::string> m(3, 3, vec);
  matrix<std::string> m2 = std::move(m);

  ASSERT_EQ(m2.size(), 9);
  ASSERT_EQ(m2.rows(), 3);
  ASSERT_EQ(m2.cols(), 3);
  ASSERT_EQ(m2(2, 2), "9");
  ASSERT_EQ(m.size(), 0);
  ASSERT_EQ(m.rows(), 0);
  ASSERT_EQ(m.cols(), 0);
  EXPECT_THROW(m.at(0, 0), std::out_of_range);
}

TEST(NFTDynamicmatrix, ChangeSizes) {
  matrix<std::string> m(3, 3, "1");
  m.rows(5);
  m.cols(5);
  ASSERT_EQ(m.rows(), 5);
  ASSERT_EQ(m.cols(), 5);
  ASSERT_EQ(m(4, 4), "");

  m.resize(3, 3);
  ASSERT_EQ(m.rows(), 3);
  ASSERT_EQ(m.cols(), 3);
  ASSERT_EQ(m(2, 2), "1");

  m.clear();
  ASSERT_EQ(m.rows(), 0);
  ASSERT_EQ(m.cols(), 0);
  EXPECT_THROW(m.at(0, 0), std::out_of_range);
}

TEST(NFTDynamicmatrix, transformUnary) {
  matrix<std::string> m(3, 3, "1");
  m.transform([](const std::string &item) { return item + "2"; });
  ASSERT_EQ(m(0, 0), "12");
}

TEST(NFTDynamicmatrix, transformBinary) {
  matrix<std::string> m1(3, 3, "1");
  matrix<std::string> m2(3, 3, "2");
  m1.transform(m2, [](const std::string &lhs, const std::string &rhs) { return lhs + rhs; });
  ASSERT_EQ(m1(0, 0), "12");
}

TEST(NFTDynamicmatrix, generate) {
  auto hello_operation = [] { return "Hello"; };

  matrix<std::string> m(3, 3, "1");
  m.generate(hello_operation);
  ASSERT_EQ(m(0, 0), "Hello");
}

TEST(NFTDynamicmatrix, mathOperationsNumber) {
  matrix<std::string> m(3, 3, "1");
  m.add("2");
  ASSERT_EQ(m(1, 2), "12");
  m += "3";
  ASSERT_EQ(m(1, 2), "123");
}

TEST(NFTDynamicmatrix, sumItems) {
  matrix<std::string> m(3, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9"
  });
  std::string sum = m.sum();
  ASSERT_EQ(sum, "123456789");
}

TEST(NFTDynamicmatrix, transposematrix) {
  matrix<std::string> m(4, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9",
	  "1", "2", "3"
  });
  matrix<std::string> transposed = m.transpose();

  matrix<std::string> correct(3, 4, {
	"1", "4", "7",
	"1", "2", "5",
	"8", "2", "3",
	"6", "9", "3"
  });
  auto begin1 = transposed.begin();
  auto end1 = transposed.end();
  auto begin2 = correct.begin();

  while (begin1 != end1) {
	ASSERT_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(NFTDynamicmatrix, minormatrix) {
  matrix<std::string> m(3, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9",
  });
  matrix<std::string> minor = m.minor(0, 0);
  ASSERT_EQ(minor.size(), 4);
  ASSERT_EQ(minor.rows(), 2);
  ASSERT_EQ(minor.cols(), 2);

  matrix<std::string> correct(2, 2, {
	"5", "6",
	"8", "9"
  });
  auto begin1 = minor.begin();
  auto end1 = minor.end();
  auto begin2 = correct.begin();

  while (begin1 != end1) {
	ASSERT_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(NFTDynamicmatrix, trace) {
  matrix<std::string> m(3, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9",
  });

  std::string trace_correct = "159";
  std::string trace = m.trace();
  ASSERT_EQ(trace, trace_correct);

  m.resize(3, 4);
  EXPECT_THROW(m.trace(), std::logic_error);
}

TEST(NFTDynamicmatrix, convestToVector) {
  matrix<std::string> m(3, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9",
  });
  std::vector<std::string> vec = m.to_vector();

  auto begin1 = m.begin();
  auto end1 = m.end();
  auto begin2 = vec.begin();

  while (begin1 != end1) {
	ASSERT_EQ(*begin1, *begin2);
	++begin1, ++begin2;
  }
}

TEST(NFTDynamicmatrix, convestTomatrixVector) {
  matrix<std::string> m(3, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9",
  });
  std::vector<std::vector<std::string>> vec = m.to_matrix_vector();

  for (size_t row = 0; row != m.rows(); ++row)
	for (size_t col = 0; col != m.cols(); ++col)
	  ASSERT_EQ(m(row, col), vec[row][col]);
}

TEST(NFTDynamicmatrix, equality) {
  matrix<std::string> m(3, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9",
  });
  matrix<std::string> m2 = m;

  auto equal = m2.equal_to(m);
  ASSERT_EQ(equal, true);

  equal = m2 == m;
  ASSERT_EQ(equal, true);
}

TEST(NFTDynamicmatrix, to_join_right) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  m.to_join_right(m2);
  matrix<std::string> m_correct(2, 4, {
	  "1", "2", "3", "4",
	  "5", "6", "7", "8"
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(NFTDynamicmatrix, join_right) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  auto join = m.join_right(m2);
  matrix<std::string> m_correct(2, 4, {
	  "1", "2", "3", "4",
	  "5", "6", "7", "8"
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(NFTDynamicmatrix, to_join_leNFT) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  m.to_join_left(m2);
  matrix<std::string> m_correct(2, 4, {
	  "3", "4", "1", "2",
	  "7", "8", "5", "6"
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(NFTDynamicmatrix, join_left) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  auto join = m.join_left(m2);
  matrix<std::string> m_correct(2, 4, {
	  "3", "4", "1", "2",
	  "7", "8", "5", "6"
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(NFTDynamicmatrix, to_join_top) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  m.to_join_top(m2);
  matrix<std::string> m_correct(4, 2, {
	  "3", "4",
	  "7", "8",
	  "1", "2",
	  "5", "6"
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(NFTDynamicmatrix, join_top) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  auto join = m.join_top(m2);
  matrix<std::string> m_correct(4, 2, {
	  "3", "4",
	  "7", "8",
	  "1", "2",
	  "5", "6"
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(NFTDynamicmatrix, to_join_bottom) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  m.to_join_bottom(m2);
  matrix<std::string> m_correct(4, 2, {
	  "1", "2",
	  "5", "6",
	  "3", "4",
	  "7", "8"
  });

  ASSERT_TRUE(m_correct.equal_to(m));
}

TEST(NFTDynamicmatrix, join_bottom) {
  matrix<std::string> m(2, 2, {
	  "1", "2",
	  "5", "6"
  });

  matrix<std::string> m2(2, 2, {
	  "3", "4",
	  "7", "8"
  });

  auto join = m.join_bottom(m2);
  matrix<std::string> m_correct(4, 2, {
	  "1", "2",
	  "5", "6",
	  "3", "4",
	  "7", "8"
  });

  ASSERT_TRUE(m_correct.equal_to(join));
}

TEST(NFTDynamicmatrix, swap_rows) {
  matrix<std::string> m(3, 3, {
	  "1", "2", "3",
	  "4", "5", "6",
	  "7", "8", "9",
  });

  m.swap_rows(0, 1);
  m.swap_rows(1, 2);

  matrix<std::string> correct(3, 3, {
	  "4", "5", "6",
	  "7", "8", "9",
	  "1", "2", "3"
  });

  bool equal = m == correct;
  ASSERT_TRUE(equal);
}

TEST(NFTDynamicmatrix, swap_cols) {
  matrix<std::string> m(3, 3, {
	  "1", "4", "7",
	  "2", "5", "8",
	  "3", "6", "9"
  });

  m.swap_cols(0, 1);
  m.swap_cols(1, 2);

  matrix<std::string> correct(3, 3, {
	  "4", "7", "1",
	  "5", "8", "2",
	  "6", "9", "3"
  });

  bool equal = m == correct;
  ASSERT_TRUE(equal);
}
