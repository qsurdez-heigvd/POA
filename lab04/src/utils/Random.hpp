/**
 * @file Declaration of the Random class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <random>

/**
 * Random class with static methods
 */
struct Random {
private:

    static std::mt19937 rng;

public:

    /**
     * Static method to get a random number between [min, max]
     * @throw invalid_argument if min is greater or equal to max
     * @param min the minimal value
     * @param max the maximal value
     * @return random int between the range given
     */
    static int generate(int min, int max);

    /**
     * Static method to get a random number between [0, max]
     * @param max the maximal value
     * @return random int between 0 and max
     */
    static int generateFrom0(size_t max);

    /**
     * Static method to get a random bool
     * @return either 1 or 0 in a random fashion
     */
    static bool randomBool();

};
