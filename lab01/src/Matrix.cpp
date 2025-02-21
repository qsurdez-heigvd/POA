#include "Matrix.hpp"
#include <random>
#include <iostream>
#include "operations/Operation.hpp"
#include "utils/utils.hpp"

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {

   for (unsigned int i = 0; i < matrix.row; i++) {
      for (unsigned int j = 0; j < matrix.column; j++) {
         os << matrix.matrix[i][j] << " ";
      }
      os << std::endl;
   }
   return os;
}

Matrix::Matrix(const unsigned int &_modulo, const unsigned int &_row, const unsigned int &_column) : modulo(_modulo),
                                                              row(_row),
                                                              column(_column) {
   if (_modulo <= 0 || _row <= 0 || _column <= 0) {
      throw std::runtime_error(
                 "The modulo, row or column cannot be equal or lower than zero"
                 );
      return;
   }

   try {
      // Allocate memory for the matrix
      matrix = new unsigned int *[row];
      matrix[0] = new unsigned int[row * column];
      for (unsigned int i = 0; i < row; i++) {
         matrix[i] = matrix[0] + i * column;
      }
   } catch (const std::bad_alloc& e) { // todo neccessary or we don't care ?
      // Memory allocation failed, handle the error here
      std::cerr << "Memory allocation failed: " << e.what() << std::endl;
      throw;
   }
   // Initialize matrix with random values
   std::random_device rd;
   std::mt19937 gen(rd()); // Mersenne_twister_engine init with rd()
   std::uniform_int_distribution<> distrib(0, static_cast<int>(modulo) - 1);
   for (unsigned int i = 0; i < row; i++) {
      for (unsigned int j = 0; j < column; j++) {
         matrix[i][j] = static_cast<unsigned int>(distrib(gen));
      }
   }

}

// The new value 1 is assigned to ensure a valid state of the object after the move.
// This allows the user to potentially reuse the object, although not recommended.
Matrix::Matrix(Matrix &&moved_matrix) noexcept
                           : modulo{std::exchange(moved_matrix.modulo, 1)},
                              row{std::exchange(moved_matrix.row, 1)},
                              column{std::exchange(moved_matrix.column,1)},
                              matrix{std::exchange(moved_matrix.matrix, nullptr)} {}

Matrix &Matrix::operator=(Matrix &&moved_matrix) noexcept {
   if (this == &moved_matrix) {
      return *this;
   }

   // Free the matrix - Neo is that u ? ◕_◕ // todo check pls
   if (matrix != nullptr) {
      if (matrix[0] != nullptr) {
         delete[] matrix[0];
      }
      delete[] matrix;
   }

   // Assign new values and ensure moved_matrix is in a valid state
   modulo = std::exchange(moved_matrix.modulo, 1);
   row = std::exchange(moved_matrix.row, 1);
   column = std::exchange(moved_matrix.column, 1);
   matrix = std::exchange(moved_matrix.matrix, nullptr);

   return *this;
}

Matrix::~Matrix() {
   // todo check pls
   if (matrix != nullptr) {
      if (matrix[0] != nullptr) {
         delete[] matrix[0];
      }
      delete[] matrix;
   }

}

Matrix::Matrix(const Matrix &matrix1) : modulo(matrix1.modulo),
                                        row(matrix1.row),
                                        column(matrix1.column) {
   // Allocate memory
   matrix = new unsigned int *[row];
   matrix[0] = new unsigned int[row * column];
   for (unsigned int i = 0; i < row; i++) {
      matrix[i] = matrix[0] + i * column;
   }
   // Copy values from matrix1
   for (unsigned int i = 0; i < row; i++) {
      for (unsigned int j = 0; j < column; j++) {
         matrix[i][j] = matrix1.matrix[i][j];
      }
   }
}

Matrix &Matrix::operator=(const Matrix &op2) {
   if (this == &op2) {
      return *this;
   }
   this->row = op2.row;
   this->column = op2.column;
   this->modulo = op2.modulo;

   // Allocate memory
   matrix = new unsigned int *[row];
   matrix[0] = new unsigned int[row * column];
   for (unsigned int i = 0; i < row; i++) {
      matrix[i] = matrix[0] + i * column;
   }
   // Copy values from op2
   for (unsigned int i = 0; i < row; i++) {
      for (unsigned int j = 0; j < column; j++) {
         this->matrix[i][j] = op2.matrix[i][j];
      }
   }

   return *this;
}

void Matrix::performOperationResult(const Matrix &op2, Matrix &result,
                                    const Operation &operation) const {
   if (this->modulo != op2.modulo) {
      throw std::invalid_argument("The modulii of the matrix must be equal");
      return;
   }
   // Perform an operation between two matrices
   // and stores the result in a third matrix
   for (unsigned int i = 0; i < result.row; i++) {
      for (unsigned int j = 0; j < result.column; j++) {
         unsigned int num1 = getValueIfInBound(*this, i, j);
         unsigned int num2 = getValueIfInBound(op2, i, j);
         unsigned int temp_int = floorMod(operation.calculate(
            static_cast<int>(num1),
            static_cast<int>(num2)
         ), static_cast<int>(result.modulo));
         result.matrix[i][j] = temp_int;
      }
   }
}

Matrix Matrix::applyOpStaticVal(const Matrix &b, const Operation &op) {
   unsigned int maxRows, maxColumns;
   getMaxRowMaxColumn(b, maxRows, maxColumns);

   // Create a Matrix object with statically allocated memory
   Matrix result = Matrix(modulo, maxRows, maxColumns);
   // Perform the operation and store the result
   performOperationResult(b, result, op);

   return result;
}

Matrix *Matrix::applyOpDynaPtr(const Matrix &b, const Operation &op) {
   unsigned int maxRows, maxColumns;
   getMaxRowMaxColumn(b, maxRows, maxColumns);
   // Create a Matrix object with dynamically allocated memory
   auto *result = new Matrix(modulo, maxRows, maxColumns);
   // Perform the operation and store the result
   performOperationResult(b, *result, op);

   return result;
}

void Matrix::applyOpModify(const Matrix &b, const Operation &op) {
   unsigned int maxRows, maxColumns;
   getMaxRowMaxColumn(b, maxRows, maxColumns);
   // Create a temporary Matrix object with dynamically allocated memory
   auto *result = new Matrix(modulo, maxRows, maxColumns);
   // Perform the operation and store the result
   performOperationResult(b, *result, op);
   // Move the result to the current matrix
   *this = std::move(*result);
}

void Matrix::getMaxRowMaxColumn(const Matrix &op2, unsigned int &maxRow,
                                unsigned int &maxColumn) const {
   maxRow = std::max(row, op2.row);
   maxColumn = std::max(column, op2.column);

}

unsigned int Matrix::getValueIfInBound(const Matrix &matrixOfInterest,
                                 const unsigned int &i, const unsigned int &j) {
   return (matrixOfInterest.row <= i || matrixOfInterest.column <= j) ?
            0 : matrixOfInterest.matrix[i][j];
}
