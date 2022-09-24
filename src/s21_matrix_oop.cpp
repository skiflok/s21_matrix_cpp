

#include "s21_matrix_oop.h"
#include <exception>



S21Matrix::S21Matrix() {
  rows = 0;
  cols = 0;
  matrix = nullptr;
}



S21Matrix::~S21Matrix() {

}



int main() {

  int *a = new int;
  delete a;
  int *arr = new int [10];
  delete [] arr;
  arr = nullptr;

  std::cout << "test\n";


  return 0;
}

//}