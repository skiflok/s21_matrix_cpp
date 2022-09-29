

#include "s21_matrix_oop.h"
#include <exception>
#include <utility>
#include <algorithm>
#include <cmath>

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

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
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

  for (int i = 0; i < res.getRows(); i++)
    for (int j = 0; j < res.getCols(); j++)
      for (int k = 0; k < this->cols; k++)
        res[i][j] += (*this)[i][k] * other[k][j];
  return res;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix res(this->rows, this->cols);
  for (int i = 0; i < res.getRows(); ++i) {
    for (int j = 0; j < res.getCols(); ++j) {
      res[i][j] = (*this)[i][j] * number;
    }
  }
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  if (this->rows != other.rows || this->cols != other.cols)
    return false;
  for (int i = 0; i < this->getRows(); i++)
    for (int j = 0; j < this->getCols(); j++)
      if (std::fabs((*this)[i][j] - other[i][j]) > 1e-07)
        return false;
  return true;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->copyMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  this->moveMatrix(std::move(other));
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (this->rows != other.cols || this->cols != other.rows)
    throw std::length_error("different matrix dimensions");

  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < this->cols; ++j) {
      (*this)[i][j] +=  other[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other){
  if (this->rows != other.cols || this->cols != other.rows)
    throw std::length_error("different matrix dimensions");

  for (int i = 0; i < this->rows; ++i) {
    for (int j = 0; j < this->cols; ++j) {
      (*this)[i][j] -=  other[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  S21Matrix res(this->rows, other.cols);
  res = *this * other;
  *this = std::move(res);
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
