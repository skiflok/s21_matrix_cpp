#include "../src/s21_matrix_oop.h"
#include <gtest/gtest.h>

TEST(Basic, defaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.getRows(), 0);
  EXPECT_EQ(m.getCols(), 0);
  EXPECT_EQ(m.getMatrix(), nullptr);
  std::cout << "test1" << "\n";
}

TEST(Basic, parameterizedCconstructor) {
  S21Matrix m1(0,2);
  EXPECT_EQ(m1.getRows(), 0);
  std::cout << "test2" << "\n";
}

//int main(int argc, char *argv[]) {
//  testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}