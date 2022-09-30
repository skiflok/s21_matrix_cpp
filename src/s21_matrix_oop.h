

#ifndef S21_MATRIX_CPP_S21_MATRIX_OOP_H
#define S21_MATRIX_CPP_S21_MATRIX_OOP_H

#include <iostream>

class S21Matrix {
 private:
  int rows, cols;    // rows and columns attributes
  double *matrix;   // pointer to the memory where the matrix will be allocated

 public:
  S21Matrix();                              // default constructor
  S21Matrix(int rows, int cols);            // parameterized constructor
  S21Matrix(const S21Matrix &other);        // copy constructor
  S21Matrix(S21Matrix &&other) noexcept;             // move constructor
  ~S21Matrix();                             // destructor

  // some operators overloads
  S21Matrix operator+(const S21Matrix &other);  //    +	Сложение двух матриц	различная размерность матриц
  S21Matrix operator-(const S21Matrix &other);  //    -	Вычитание одной матрицы из другой	различная размерность матриц
  S21Matrix operator*(const S21Matrix &other);  //    *	Умножение матриц число столбцов первой матрицы не равно числу строк второй матрицы
  S21Matrix operator*(double number);     //     умножение матрицы на число
  bool operator==(const S21Matrix &other);      //     ==	Проверка на равенство матриц (eq_matrix)
  S21Matrix &operator=(const S21Matrix &other); //     =	Присвоение матрице значений другой матрицы
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);  // +=	Присвоение сложения (sum_matrix)	различная размерность матриц
  S21Matrix &operator-=(const S21Matrix &other);    // -=	Присвоение разности (sub_matrix)	различная размерность матриц
  S21Matrix &operator*=(const S21Matrix &other);    //   *=	Присвоение умножения (mul_matrix/mul_number)
  S21Matrix &operator*=(double number);       // *=	Присвоение умножения (mul_matrix/mul_number)

  // assignment operator overload
  double &operator()(int row,
                     int col);    //Индексация по элементам матрицы (строка, колонка)	индекс за пределами матрицы
  double *operator[](int i) const;

  // some public methods
  bool eqMatrix(const S21Matrix &other);            //Проверяет матрицы на равенство между собой
  void sumMatrix(const S21Matrix &other);         //Прибавляет вторую матрицы к текущей	различная размерность матриц
  void subMatrix(const S21Matrix &other);       //Вычитает из текущей матрицы другую	различная размерность матриц
  void mulNumber(double num);               //Умножает текущую матрицу на число
  void mulMatrix(const S21Matrix &other);         //	Умножает текущую матрицу на вторую	число столбцов первой матрицы не равно числу строк второй матрицы
  S21Matrix transpose();                          //	Создает новую транспонированную матрицу из текущей и возвращает ее
  S21Matrix calcComplements();                 //	Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее	матрица не является квадратной
  double determinant();                     //	Вычисляет и возвращает определитель текущей матрицы	матрица не является квадратной
  S21Matrix inverseMatrix();                //	Вычисляет и возвращает обратную матрицу	определитель матрицы равен 0


// getters and setters

  int getRows() const;
  int getCols() const;
  double *getMatrix() const;
  void setRows(int new_rows);
  void setCols(int new_cols);

  // support function

  void setZeroMatrix();
  void createMatrix();
  void copyMatrix(const S21Matrix &other);
  void moveMatrix(S21Matrix &&other);
  void removeMatrix();
  bool swapRows(int position);
  S21Matrix subRowMultByMultiplier(int originRow, int subRow, double multiplier);
  S21Matrix minorMatrix();
  S21Matrix getDecMatrix(S21Matrix &other, int rowIndex, int colIndex);

};

#endif //S21_MATRIX_CPP_S21_MATRIX_OOP_H
