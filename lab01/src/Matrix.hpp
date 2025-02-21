#pragma once

#include <ostream>
#include <random>
#include <cmath>
#include "operations/Operation.hpp"

class Matrix {

private:
   unsigned int modulo;      /**< Modulo value for the matrix. */
   unsigned int row;         /**< Number of rows in the matrix. */
   unsigned int column;      /**< Number of columns in the matrix. */
   unsigned int** matrix;    /**< Pointer to the matrix data. */

   /**
    * @brief Helper function to get the value at a specific position in the matrix
    *        if it's in bounds.
    * @param matrixOfInterest Matrix to get the value from.
    * @param i Row index.
    * @param j Column index.
    * @return Value at the specified position, or 0 if out of bounds.
    */
   [[nodiscard]] static unsigned int getValueIfInBound(const Matrix &matrixOfInterest,
                                                 const unsigned int &i, const unsigned int &j);

   /**
    * @brief Performs an operation between two matrices and stores the result
    *       in a third matrix.
    * @param op2 Second matrix for the operation.
    * @param result Resultant matrix to store the operation result.
    * @param operation Operation to be performed.
    */
   void performOperationResult(const Matrix &op2, Matrix &result,
                               const Operation &operation) const;

   /**
    * @brief Helper function to get the maximum rows and columns between two
    *        matrices.
    * @param op2 Second matrix for comparison.
    * @param maxRow Maximum rows.
    * @param maxColumn Maximum columns.
    */
   void getMaxRowMaxColumn(const Matrix &op2, unsigned int &maxRow,
                           unsigned int &maxColumn) const;

public:
   /**
    * @brief Constructor to initialize a matrix with specified modulo, rows,
    *       and columns.
    * @param _modulo Modulo value for the matrix.
    * @param _row Number of rows in the matrix.
    * @param _column Number of columns in the matrix.
    */
   Matrix(const unsigned int &_modulo, const unsigned int &_row, const unsigned int &_column);

   /**
    * @brief Destructor to release memory allocated for the matrix.
    */
   ~Matrix();

   /**
    * @brief Copy constructor to perform deep copy of another matrix.
    * @param matrix1 Matrix to be copied.
    */
   Matrix(const Matrix& matrix1);

   /**
    * @brief Copy assignment operator to perform deep copy of another matrix.
    * @param op2 Matrix to be assigned.
    * @return Reference to the assigned matrix.
    */
   Matrix& operator=(const Matrix& op2);

   /**
    * @brief Move constructor.
    * @param moved_matrix Matrix to be moved.
    */
   Matrix(Matrix&& moved_matrix) noexcept;

   /**
    * @brief Move assignment operator.
    * @param moved_matrix Matrix to be moved.
    * @return Reference to the assigned matrix.
    */
   Matrix& operator=(Matrix&& moved_matrix) noexcept;

   /**
    * @brief Applies a static operation on a matrix with a given operation.
    * @param b Second matrix for the operation.
    * @param op Operation to be performed.
    * @return Resultant matrix after applying the operation.
    */
   Matrix applyOpStaticVal(const Matrix& b, const Operation& op);

   /**
     * @brief Applies an operation on the current matrix and modifies it.
     * @param b Second matrix for the operation.
     * @param op Operation to be performed.
     */
   void applyOpModify(const Matrix& b, const Operation& op);

   /**
     * @brief Applies a dynamic operation on a matrix with a given operation.
     * @param b Second matrix for the operation.
     * @param op Operation to be performed.
     * @return Pointer to the resultant matrix after applying the operation.
     */
   Matrix* applyOpDynaPtr(const Matrix& b, const Operation& op);

   /**
    * @brief Overloaded stream insertion operator to print the matrix.
    * @param os Output stream.
    * @param matrix Matrix to be printed.
    * @return Reference to the output stream.
    */
   friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

};
