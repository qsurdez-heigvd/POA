/**
 * @file Declaration of the FieldStatsCalculator struct
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <cstddef>
#include "../field/Field.hpp"

/**
 * Structure to calculate the statistics of n simulations.
 */
struct FieldStatsCalculator {
    static double simulate(size_t height, size_t width, size_t nbVampire, size_t nbHuman, size_t nbSimulations=10000);
};

