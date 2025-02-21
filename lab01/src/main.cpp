#include <iostream>
#include "Matrix.hpp"
#include "src/operations/Addition.hpp"
#include "src/operations/Subtraction.hpp"
#include "src/operations/Multiplication.hpp"

int main(int argc, char **argv) {

   if (argc != 6) {
      std::cout << "The arguments are as followed : N1, M1, N2, M2, modulo.";
      return 1;
   }

   for (int i = 1; i < argc; i++) {
      char *arg = argv[i];
      while (*arg != '\0') {
         if (!isdigit(*arg)) {
            std::cerr << "Error: Argument " << i << " is not an integer" << std::endl;
            return EXIT_FAILURE;
         }
         arg++;
      }
   }

   unsigned int row1 = static_cast<unsigned int>(std::stoull(argv[1]));
   unsigned int column1 = static_cast<unsigned int>(std::stoull(argv[2]));

   unsigned int row2 =static_cast<unsigned int>( std::stoull(argv[3]));
   unsigned int column2 = static_cast<unsigned int>(std::stoull(argv[4]));

   unsigned int modulo = static_cast<unsigned int>(std::stoull(argv[5]));

   std::cout << "The modulus is " << modulo << "\n\n";

   Matrix m1 = Matrix(modulo, row1, column1);
   Matrix m2 = Matrix(modulo, row2, column2);

   Matrix *resultAddition = m1.applyOpDynaPtr(m2, Addition());
   Matrix resultSubtraction = m1.applyOpStaticVal(m2, Subtraction());

   std::cout << "one\n" << m1 << "\n";

   std::cout << "two\n" << m2 << "\n";

   std::cout << "one + two\n" << *resultAddition << "\n";

   std::cout << "one - two\n" << resultSubtraction << "\n";

   m1.applyOpModify(m2, Multiplication());

   std::cout << "one x two\n" << m1 << std::endl;

   return EXIT_SUCCESS;
}