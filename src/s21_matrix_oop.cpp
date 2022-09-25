

#include "s21_matrix_oop.h"
#include <exception>



S21Matrix::S21Matrix() {
  this->cols = 0;
  this->rows = 0;
  this->matrix = nullptr;
  std::cout << "default constructor" << "\n";
}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
  std::cout << "parameter constructor" << "\n";
}


int S21Matrix::GetRows() const {
  return rows;
}
int S21Matrix::GetCols() const {
  return cols;
}
double **S21Matrix::GetMatrix() const {
  return matrix;
}

void S21Matrix::setZeroMatrix() {
  this->cols = 0;
  this->rows = 0;
  this->matrix = nullptr;
}



S21Matrix::~S21Matrix() {
//  delete matrix;
}



//int main() {
//
//  int *a = new int;
//  delete a;
//  int *arr = new int [10];
//  delete [] arr;
//  arr = nullptr;
//
//  std::cout << "test\n";
//
////  S21Matrix m(3, 4);
//
//  S21Matrix m;
//
//
//  std::cout << m.GetRows() << "  " << m.GetCols() << "\n";
//
//
//  return 0;
//}
