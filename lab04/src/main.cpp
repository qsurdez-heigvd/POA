#include <iostream>
#include <algorithm>
#include "field/Field.hpp"
#include "display/FieldController.hpp"

bool isNumber(const std::string &s) {
   return !s.empty() && std::find_if(s.begin(), s.end(),
                                     [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main(int argc, char **argv) {
   if (argc != 5) {
      std::cerr << "Usage: " << argv[0] << " <width> <height> <nbVampire> <nbHuman>" << std::endl;
      return 1;
   }

   if (!isNumber(argv[1]) || !isNumber(argv[2]) || !isNumber(argv[3]) || !isNumber(argv[4])) {
      std::cerr << "Invalid parameters. All parameters must be numbers." << std::endl;
      return 1;
   }

   int width = std::atoi(argv[1]);
   int height = std::atoi(argv[2]);
   int nbVampire = std::atoi(argv[3]);
   int nbHuman = std::atoi(argv[4]);

   if (width <= 0 || height <= 0 || nbVampire < 0 || nbHuman < 0) {
      std::cerr << "Invalid parameters. All numbers must be non-negative,"
                   " and dimensions must be positive." << std::endl;
      return 1;
   }
   Field field{static_cast<size_t>(height),
               static_cast<size_t>(width),
               static_cast<size_t>(nbVampire),
               static_cast<size_t>(nbHuman)};
   FieldController controller{field};

   std::cout << "Simulation is running..." << std::endl;
   controller.start();
   std::cout << "Simulation is finished." << std::endl;
   return 0;
}