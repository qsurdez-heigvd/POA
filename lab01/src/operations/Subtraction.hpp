#pragma once
#include "Operation.hpp"

/**
 * @brief The Subtraction class represents a subtraction operation.
 */
class Subtraction : public Operation {
public:
   /**
    * @brief Default constructor for Subtraction.
    */
   Subtraction() = default;

   /**
    * @brief Calculates the result of subtraction.
    * @param a The first operand.
    * @param b The second operand.
    * @return The result of subtraction.
    */
    [[nodiscard]] int calculate(const int& a,
                                        const int& b) const override;
};