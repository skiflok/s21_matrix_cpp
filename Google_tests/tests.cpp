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

TEST(GetterAndSetter, setRows) {

  S21Matrix m(2, 3);
  m[1][1] = 4.4;
  EXPECT_EQ(m(1,1), 4.4);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
  m.setRows(4);
  m[3][2] = 5.5;
  EXPECT_EQ(m(1,1), 4.4);
  EXPECT_EQ(m(3,2), 5.5);
  EXPECT_EQ(m.getRows(), 4);
  EXPECT_EQ(m.getCols(), 3);
}

TEST(GetterAndSetter, setCols) {

  S21Matrix m(2, 3);
  m[1][1] = 4.4;
  EXPECT_EQ(m(1,1), 4.4);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
  m.setCols(5);
  m[1][4] = 5.5;
  EXPECT_EQ(m(1,1), 4.4);
  EXPECT_EQ(m(1,4), 5.5);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 5);
}

TEST(assignmentOperator, brakets) {
  S21Matrix m(2, 3);
  m(1, 1) = 3;
  EXPECT_EQ(m(1, 1), 3);
  EXPECT_EQ(m[1][1], 3);
}

TEST(assignmentOperator, braketsTrow) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m(1, 5));
}

TEST(assignmentOperator, brakets2) {
  S21Matrix m(2, 3);
  m[1][1] = 3;
  EXPECT_EQ(m(1, 1), 3);
  EXPECT_EQ(m[1][1], 3);
}

TEST(assignmentOperator, braketsTrow2) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m[2][5]);
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
  int rows = 2, cols = 3;
  S21Matrix test(rows, cols);
//  std::cout << test[0][0] << "\t";
  test[1][2] = 2;
  test(1, 1) = 1;
  std::cout << test[1][2] << "\t";
  std::cout << test(1, 1) << "\t\n";

//  for (int i = 0; i < rows * cols; ++i) {
////    p[i] = i;
//    std::cout << test.matrix[i] << "\t";
//  }
}

