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
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
  m.setRows(4);
  m[3][2] = 5.5;
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m(3, 2), 5.5);
  EXPECT_EQ(m.getRows(), 4);
  EXPECT_EQ(m.getCols(), 3);
}

TEST(GetterAndSetter, setCols) {

  S21Matrix m(2, 3);
  m[1][1] = 4.4;
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
  m.setCols(5);
  m[1][4] = 5.5;
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m(1, 4), 5.5);
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

TEST(functionalTest, operationPlus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  S21Matrix res = a + b;
  EXPECT_DOUBLE_EQ(res[1][1], 3.3);
}

TEST(functionalTest, operationPlusEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a + b);
}

TEST(functionalTest, operationPlus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a[1][1], 3.3);
}

TEST(functionalTest, operationPlusEx2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(functionalTest, operatiorMinus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  S21Matrix res = a - b;
  EXPECT_DOUBLE_EQ(res[1][1], -1.1);
}

TEST(functionalTest, operatiorMinusEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a + b);
}

TEST(functionalTest, operatiorMinus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a[1][1], -1.1);
}

TEST(functionalTest, operatiorMinusEx2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(functionalTest, operatiorMultMatrix) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a[1][1] = 1.1;
  b[1][1] = 2;
  S21Matrix res = a * b;
  EXPECT_DOUBLE_EQ(res[1][1], 2.2);
}

TEST(functionalTest, operatiorMultMatrixEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a * b);
}

TEST(functionalTest, operatiorMultMatrix2) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a[1][1] = 1.1;
  b[1][1] = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a[1][1], 2.2);
}

TEST(functionalTest, operatiorMultMatrixEx2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a[1][1] = 1.1;
  b[1][1] = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(functionalTest, operatiorMultMatrixNum) {
  S21Matrix a(3, 2);
  a[1][1] = 1.1;
  S21Matrix res = a * 2;
  EXPECT_DOUBLE_EQ(res[1][1], 2.2);
}

TEST(functionalTest, operatiorMultMatrixNum2) {
  S21Matrix a(3, 2);
  a[1][1] = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a[1][1], 2.2);
}

TEST(functionalTest, equal) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, false);
  b.setCols(3);
  a[1][1] = 1.1;
  b[1][1] = 1.1;
  EXPECT_EQ(a == b, true);
  b[1][2] = 1.1;
  EXPECT_EQ(a == b, false);
}



//TEST(myTest, TestName) {
////  int *p = new int[10];
////  for (int i = 0; i < 10; ++i) {
////    p[i] = i;
////    std::cout << p[i] << "\t";
////  }
////
//  int rows = 2, cols = 3;
//  S21Matrix test(rows, cols);
////  std::cout << test[0][0] << "\t";
//  test[1][2] = 2;
//  test(1, 1) = 1;
//  std::cout << test[1][2] << "\t";
//  std::cout << test(1, 1) << "\t\n";
//
////  for (int i = 0; i < rows * cols; ++i) {
//////    p[i] = i;
////    std::cout << test.matrix[i] << "\t";
////  }
//}

