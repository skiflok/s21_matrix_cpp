#include "../src/s21_matrix_oop.h"
#include <gtest/gtest.h>
#include <utility>

TEST(Basic, defaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(m.getCols(), 0);
  EXPECT_EQ(m.getMatrix(), nullptr);
//  std::cout << "test1" << "\n";
}

TEST(Basic, parameterizedCconstructor) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
}

TEST(Basic, copyConstructor) {
  S21Matrix m(2, 3);
  S21Matrix copy(m);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 3);
  // need equals test
}

TEST(Basic, moveConstructor) {
  S21Matrix m(2, 3);
  S21Matrix res(std::move(m));
  EXPECT_EQ(res.getRows(), 2);
  EXPECT_EQ(res.getCols(), 3);
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(m.getCols(), 0);
  EXPECT_EQ(m.getMatrix(), nullptr);
}

TEST(supportFunction, removeAndSetZeroMatrix) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
  m.removeMatrix();
  m.setZeroMatrix();
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(m.getCols(), 0);
  EXPECT_EQ(m.getMatrix(), nullptr);
}

TEST(myTest, TestName) {
//  int *p = new int[10];
//  for (int i = 0; i < 10; ++i) {
//    p[i] = i;
//    std::cout << p[i] << "\t";
//  }
//
  S21Matrix test(2, 3);
//  std::cout << test[0][0] << "\t";
//  test(0,0) = 1;
  std::cout << test.getMatrix()[1] << "\t";
  test.getMatrix()[1];

}
