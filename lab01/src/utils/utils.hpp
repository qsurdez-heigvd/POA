#pragma once

#include <cstdlib>

/**
 * Caclulate number % mod and ensure that the result is positive
 * @param number the number on which to apply the modulo
 * @param mod the modulo
 * @return number % mod (>= 0)
 */
unsigned int floorMod(const int &number, const int &mod);