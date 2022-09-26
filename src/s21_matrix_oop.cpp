

#include "s21_matrix_oop.h"
#include <exception>

S21Matrix::S21Matrix() {
  setZeroMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
  this->matrix = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    this->matrix[i] = new double[cols];
  }
}

int S21Matrix::getRows() const {
  return rows;
}
int S21Matrix::getCols() const {
  return cols;
}
double **S21Matrix::getMatrix() const {
  return matrix;
}

void S21Matrix::setZeroMatrix() {
  this->cols = 0;
  this->rows = 0;
  this->matrix = nullptr;
}

S21Matrix::~S21Matrix() {
//  try {
//    for (int i = 0; i < rows; ++i) {
//      delete[] matrix[i];
//    }
//    delete[] matrix;
//    matrix = nullptr;
//    rows = 0;
//    cols = 0;
//  } catch (std::exception) {
//
//  }
  if (matrix != nullptr) {
    for (int i = 0; i < rows; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
    rows = 0;
    cols = 0;
  }
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
