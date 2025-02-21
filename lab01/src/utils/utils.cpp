#include "utils.hpp"

unsigned int floorMod(const int &number, const int &mod){
   int result = number % mod;
   if (result < 0){
      return static_cast<unsigned int>(result + mod);
   }
   return static_cast<unsigned int>(result);
}
