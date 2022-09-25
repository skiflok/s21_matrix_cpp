#include "../src/s21_matrix_oop.h"
#include <gtest/gtest.h>

TEST(Basic, defaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  std::cout << "test test test";
}

TEST(Basic, parameterizedCconstructor) {
  S21Matrix m(3, 3);
  EXPECT_EQ(m.GetRows(), 3);
}
