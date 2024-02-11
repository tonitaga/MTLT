#include <mtlt/adapters.h>
#include <mtlt/matrix.h>

#include <gtest/gtest.h>

using namespace std;
using namespace mtlt;

TEST(FTReverseAdapter, Matrix) {
  matrix<int> matrix(3, 3, {
	1, 2, 3,
	4, 5, 6,
	7, 8, 9
  });

  vector<int> reversed;
  reversed.reserve(matrix.size());

  vector<int> correct { 9, 8, 7, 6, 5, 4, 3, 2, 1 };

  for (int num : reverse(matrix)) {
	reversed.push_back(num);
  }

  ASSERT_EQ(reversed, correct);
}

TEST(FTReverseAdapter, Vector) {
  vector<int> vec { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  vector<int> reversed;
  reversed.reserve(vec.size());

  vector<int> correct { 9, 8, 7, 6, 5, 4, 3, 2, 1 };

  for (int num : reverse(vec)) {
	reversed.push_back(num);
  }

  ASSERT_EQ(reversed, correct);
}