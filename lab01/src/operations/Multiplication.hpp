#pragma once
#include "Operation.hpp"

/**
 * @brief The Multiplication class represents a multiplication operation.
 */
class Multiplication : public Operation {
public:
   /**
    * @brief Default constructor for Multiplication.
    */
   Multiplication() = default;

   /**
    * @brief Calculates the result of multiplication.
    * @param a The first operand.
    * @param b The second operand.
    * @return The result of multiplication.
    */
   [[nodiscard]] int calculate(const int& a,
                                        const int& b) const override;
};