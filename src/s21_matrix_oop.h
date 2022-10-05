#ifndef SRC_S21_MATRIX_OOP_H
#define SRC_S21_MATRIX_OOP_H

namespace s21_matrix_oop {

class S21Matrix {
 public:
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix &other);      // copy constructor
  S21Matrix(S21Matrix &&other) noexcept;  // move constructor
  ~S21Matrix();                           // destructor

  // operators overloads
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double number);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double number);

  // assignment operator overload
  double &operator()(int row, int col);
  double &operator()(int row, int col) const;

  //  public methods
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  /**
   * вычисляет матрицу миноров
   * @return возвращает матрицу миноров
   */
  S21Matrix MinorMatrix();

  // getters and setters

  int GetRows() const;
  int GetCols() const;
  double *GetMatrix() const;
  /**
   * устанавливает новое количество колонок
   * @param new_rows
   */
  void SetRows(int new_rows);
  /**
   * устанавливает новое количество колонок
   * при увеличении заполняет нулями
   * при уменьшении отбрасывает значения
   * @param new_cols новое количество колонок
   */
  void SetCols(int new_cols);

 private:
  int rows_, cols_;
  double *matrix_;

  // support function

  /**
   * устанавливает поля класса в 0 и nullptr
   */
  void SetZeroMatrix();

  /**
   * выделяет память в виде одномерного массива
   */
  void CreateMatrix();

  /**
   * копирует экземпляр класса
   * @param other
   */
  void CopyMatrix(const S21Matrix &other);
  /**
   * перемещает экземпляр класса
   * @param other
   */
  void MoveMatrix(S21Matrix &&other);

  /**
   * очищает память
   */
  void RemoveMatrix();
  /**
   * пытается поменять строку с 0 на главной диагонали на строку с !0
   * @param position индекс нуля на главной диагонали
   * @return вернет true если удалось успешно заменить строку
   */
  bool SwapRows(int position);

  /**
   * вычитает из строки строку умноженную на множитель
   * @param originRow вычитаемая строка
   * @param subRow вычитающая
   * @param multiplier множитель
   * @return
   */
  S21Matrix SubRowMultByMultiplier(int originRow, int subRow,
                                   double multiplier);

  /**
   * формирует матрицу в которой исключены столбцы и строки для поиска матрицы
   * миноров
   * @param other временная матрица
   * @param rowIndex позиция строки
   * @param colIndex позиция столбца
   * @return сформированная матрица -1 размерностью
   */
  S21Matrix GetDecMatrix(S21Matrix &other, int rowIndex, int colIndex);
};

}  // namespace s21_matrix_oop

#endif  // SRC_S21_MATRIX_OOP_H
