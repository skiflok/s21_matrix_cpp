#include "../src/s21_matrix_oop.h"
#include <gtest/gtest.h>

TEST(Basic, defaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(m.getCols(), 0);
  EXPECT_EQ(m.getMatrix(), nullptr);
//  std::cout << "test1" << "\n";
}

TEST(Basic, parameterizedCconstructor) {
  S21Matrix m(2,3);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
}

TEST(Basic, copyConstructor) {
  S21Matrix m(2,3);
  S21Matrix copy(m);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 3);
  // need equals test
}


TEST(supportFunction, removeAndSetZeroMatrix) {
  S21Matrix m(2,3);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
  m.removeMatrix();
  m.setZeroMatrix();
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(m.getCols(), 0);
  EXPECT_EQ(m.getMatrix(), nullptr);
}
