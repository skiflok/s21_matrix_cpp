

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

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (this->rows != other.rows || this->cols != other.cols)
    throw std::logic_error("different matrix dimensions");
  S21Matrix res(this->rows, this->cols);
  for (int i = 0; i < res.getRows(); ++i) {
    for (int j = 0; j < res.getCols(); ++j) {
      res[i][j] = (*this)[i][j] + other[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (this->rows != other.rows || this->cols != other.cols)
    throw std::logic_error("different matrix dimensions");
  S21Matrix res(this->rows, this->cols);
  for (int i = 0; i < res.getRows(); ++i) {
    for (int j = 0; j < res.getCols(); ++j) {
      res[i][j] = (*this)[i][j] - other[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {

  if (this->rows != other.cols || this->cols != other.rows)
    throw std::length_error("different matrix dimensions");
  S21Matrix res(this->rows, other.cols);

  for (uint32_t i = 0; i < res.getRows(); i++)
    for (uint32_t j = 0; j < res.getCols(); j++)
      for (uint32_t k = 0; k < this->cols; k++)
        res[i][j] += (*this)[i][k] * other[k][j];

  return res;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->copyMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  this->moveMatrix(std::move(other));
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
      tmp[i][j] = (*this)[i][j];
    }
  }
  this->moveMatrix(std::move(tmp));
}

void S21Matrix::setCols(int new_cols) {
  if (new_cols <= 0)
    throw std::length_error("Array size can't be zero");

  S21Matrix tmp(this->rows, new_cols);
  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < (new_cols < this->cols ? new_cols : this->cols); ++j) {
      tmp[i][j] = (*this)[i][j];
    }
  }
  this->moveMatrix(std::move(tmp));
}

// assignment operator overload

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows || col >= cols) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix[row * cols + col];
}

double *S21Matrix::operator[](int row) const {
  if (row >= this->rows)
    throw std::out_of_range("Incorrect input, index is out of range");
  return row * this->cols + this->matrix;
}

// support function

void S21Matrix::setZeroMatrix() {
  this->cols = 0;
  this->rows = 0;
  this->matrix = nullptr;
}

void S21Matrix::createMatrix() {
  this->matrix = new double[rows * cols]{};
}

void S21Matrix::removeMatrix() {
  delete[] this->matrix;
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
  this->rows = other.rows;
  this->cols = other.cols;
  this->createMatrix();
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
