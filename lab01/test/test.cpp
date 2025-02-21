#include <gtest/gtest.h>
#include "src/Matrix.hpp"
#include "src/operations/Addition.hpp"
#include "src/operations/Subtraction.hpp"
#include "src/operations/Multiplication.hpp"
#include <string>
#include <sstream>

TEST(MatrixConstructor, MatrixConstructorWrongArguments) {
   EXPECT_THROW({
                   try {
                      Matrix matrix = Matrix(5, 0, 3);
                   } catch (std::runtime_error &re) {
                      EXPECT_STREQ("The modulo, row or column cannot be equal or lower than zero", re.what());
                      throw;
                   }
                }, std::runtime_error);
   EXPECT_THROW({
                   try {
                      Matrix matrix = Matrix(5, 1, 0);
                   } catch (std::runtime_error &re) {
                      EXPECT_STREQ("The modulo, row or column cannot be equal or lower than zero", re.what());
                      throw;
                   }
                }, std::runtime_error);
   EXPECT_THROW({
                   try {
                      Matrix matrix = Matrix(0, 1, 5);
                   } catch (std::runtime_error &re) {
                      EXPECT_STREQ("The modulo, row or column cannot be equal or lower than zero", re.what());
                      throw;
                   }
                }, std::runtime_error);
}


TEST(MatrixConstructor, MatrixConstructorCorrectArguments) {
   try {
      Matrix matrix = Matrix(4, 2, 5);
      SUCCEED();
   } catch (std::runtime_error &re) {
      FAIL() << re.what();
   }
}

TEST(MatrixConstructor, MatrixConstructorElementsAreInBetweenZeroAndModulo) {
   unsigned modulo = 5;
   std::stringstream ss;
   std::string temp_str;
   int temp_int;
   bool isBetween;
   Matrix matrix = Matrix(modulo, 3, 3);

   ss << matrix;
   while (!ss.eof()) {
      ss >> temp_str;
      if (std::stringstream(temp_str) >> temp_int) {
         if (temp_int >= modulo) {
            EXPECT_LT(temp_int, modulo);
         }
      }
   }
}

TEST(MatrixOperation, MatrixOperationDifferentModulii) {
   size_t modulo1 = 4;
   size_t modulo2 = 5;

   Matrix m1 = Matrix(modulo1, 4, 4);
   Matrix m2 = Matrix(modulo2, 3, 5);

   EXPECT_THROW({
                   try {
                      m1.applyOpModify(m2, Addition());
                   } catch (std::invalid_argument &ia) {
                      EXPECT_STREQ("The modulii of the matrix must be equal", ia.what());
                      throw;
                   }
                }, std::invalid_argument);
   EXPECT_THROW({
                   try {
                      Matrix *m3 = m1.applyOpDynaPtr(m2, Addition());
                   } catch (std::invalid_argument &ia) {
                      EXPECT_STREQ("The modulii of the matrix must be equal", ia.what());
                      throw;
                   }
                }, std::invalid_argument);

   EXPECT_THROW({
                   try {
                      Matrix m3 = m1.applyOpStaticVal(m2, Addition());
                   } catch (std::invalid_argument &ia) {
                      EXPECT_STREQ("The modulii of the matrix must be equal", ia.what());
                      throw;
                   }
                }, std::invalid_argument);
}

TEST(MatrixOperation, MatrixOperationSameModulii) {

   size_t modulo1 = 5;
   size_t modulo2 = 5;

   Matrix m1 = Matrix(modulo1, 4, 4);
   Matrix m2 = Matrix(modulo2, 3, 5);

   try {
      m1.applyOpModify(m2, Addition());
   } catch (std::invalid_argument &ia) {
      FAIL() << ia.what();
   }

   try {
      m1.applyOpDynaPtr(m2, Addition());
   } catch (std::invalid_argument &ia) {
      FAIL() << ia.what();
   }

   try {
      m1.applyOpStaticVal(m2, Addition());
   } catch (std::invalid_argument &ia) {
      FAIL() << ia.what();
   }

   SUCCEED();
}

int main(int argc, char **argv) {

   unsigned int modulo = 3;

   unsigned int row1 = 2;
   unsigned int column1 = 5;

   unsigned int row2 = 4;
   unsigned int column2 = 3;

   Matrix m1 = Matrix(modulo, row1, column1);
   Matrix m2 = Matrix(modulo, row2, column2);

   std::cout << "one\n" << m1 << "\n";

   std::cout << "two\n" << m2 << "\n";

   std::cout << "Static operations: \n";

   Matrix resultAdditionStatic = m1.applyOpStaticVal(m2, Addition());
   Matrix resultSubtractionStatic = m1.applyOpStaticVal(m2, Subtraction());
   Matrix resultMultiplicationStatic = m1.applyOpStaticVal(m2, Multiplication());

   std::cout << "Addition: \n" << resultAdditionStatic << "\n";
   std::cout << "Subtraction: \n" << resultSubtractionStatic << "\n";
   std::cout << "Multiplication: \n" << resultMultiplicationStatic << "\n";

   std::cout << "Dynamic operations: \n";

   Matrix *resultAdditionDyna = m1.applyOpDynaPtr(m2, Addition());
   Matrix *resultSubtractionDyna = m1.applyOpDynaPtr(m2, Subtraction());
   Matrix *resultMultiplicationDyna = m1.applyOpDynaPtr(m2, Multiplication());

   std::cout << "Addition: \n" << *resultAdditionDyna << "\n";
   std::cout << "Subtraction: \n" << *resultSubtractionDyna << "\n";
   std::cout << "Multiplication: \n" << *resultMultiplicationDyna << "\n";

   std::cout << "Modify operations: \n";

   Matrix oldM1 = Matrix(m1);

   m1.applyOpModify(m2, Addition());

   std::cout << "Addition: \n" << m1 << "\n";

   m1 = oldM1;

   m1.applyOpModify(m2, Subtraction());

   std::cout << "Subtraction: \n" << m1 << "\n";

   m1 = oldM1;

   m1.applyOpModify(m2, Multiplication());

   std::cout << "Multiplication: \n" << m1 << "\n";

   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}