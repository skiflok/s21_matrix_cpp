

#include "s21_matrix_oop.h"
#include <exception>
#include <utility>
#include <algorithm>

S21Matrix::S21Matrix() {
  setZeroMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
  this->createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->setZeroMatrix();
  std::swap(this->rows, other.rows);
  std::swap(this->cols, other.cols);
  std::swap(this->matrix, other.matrix);
}

S21Matrix::~S21Matrix() {
  if (matrix != nullptr) {
    this->removeMatrix();
    this->setZeroMatrix();
  }
}
// some operators overloads

S21Matrix &S21Matrix::operator=(const S21Matrix &other){

  return *this;
}


// getters and setters

int S21Matrix::getRows() const {
  return rows;
}
int S21Matrix::getCols() const {
  return cols;
}
double *S21Matrix::getMatrix() const {
  return matrix;
}

void S21Matrix::setRows(int new_rows) {
  if (new_rows <= 0)
    throw std::length_error("Array size can't be zero");

  S21Matrix tmp(new_rows, this->cols);
  for (int i = 0; i < (new_rows < this->rows ? new_rows : this->rows); ++i) {
    for (int j = 0; j < this->cols; ++j) {
      tmp[i][j] = (*this) [i][j];
    }
  }
  this->moveMatrix(std::move(tmp));
}

void S21Matrix::setCols(int cols) {

}

// assignment operator overload

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows || col >= cols) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix[row * cols + col];
}

double *S21Matrix::operator[](int row){
  if (row >= this->rows)
    throw std::out_of_range("Incorrect input, index is out of range");
  return  row * this->cols + this->matrix;
}

// support function

void S21Matrix::setZeroMatrix() {
  this->cols = 0;
  this->rows = 0;
  this->matrix = nullptr;
}

void S21Matrix::createMatrix() {
//  this->matrix = new double *[rows];
//  for (int i = 0; i < rows; ++i) {
//    this->matrix[i] = new double[cols];
//  }
  this->matrix = new double [rows * cols]{};
}

void S21Matrix::removeMatrix() {
//  if (this->matrix != nullptr) {
//    for (int i = 0; i < this->rows; ++i) {
//      delete[] this->matrix[i];
//    }
    delete[] this->matrix;
//  }
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
  this->rows = other.rows;
  this->cols = other.cols;
  this->createMatrix();
//  for (int i = 0; i < this->rows; ++i) {
//    for (int j = 0; j < this->cols; ++j) {
//      this->matrix[i][j] = other.matrix[i][j];
//    }
//  }
  std::copy(other.matrix, other.matrix + rows * cols, this->matrix);
}

void S21Matrix::moveMatrix(S21Matrix &&other) {
  this->removeMatrix();
  this->setZeroMatrix();
  std::swap(this->rows, other.rows);
  std::swap(this->cols, other.cols);
  std::swap(this->matrix, other.matrix);
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
