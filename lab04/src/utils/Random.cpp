/**
 * @file Implementation of the Random class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Random.hpp"
#include <chrono>

std::mt19937 Random::rng(
        static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())
);

int Random::generate(int min, int max) {
   if (min >= max) {
      throw std::invalid_argument("Min must be smaller than max");
   }

   std::uniform_int_distribution<int> int_dist(min, max); // range [min, max[

   return int_dist(rng);
}

int Random::generateFrom0(size_t max) {
   return Random::generate(0, static_cast<int>(max));
}

bool Random::randomBool() {
   int rand = generate(0, 1);
   return rand == 1;
}