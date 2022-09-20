

#include "s21_matrix_oop.h"
#include <exception>


S21Matrix::S21Matrix() {

}

S21Matrix::~S21Matrix() {

}



int main() {

  int *a = new int;
  delete a;
  int *arr = new int [10];
  delete [] arr;
  arr = nullptr;


  return 0;
}

//}