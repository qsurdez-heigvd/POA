#pragma once
#include "Operation.hpp"

/**
 * @brief The Addition class represents an addition operation.
 */
class Addition : public Operation {
public:
   /**
    * @brief Default constructor for Addition.
    */
   Addition() = default;

   /**
    * @brief Calculates the result of addition.
    * @param a The first operand.
    * @param b The second operand.
    * @return The result of addition.
    */
   [[nodiscard]] int calculate(const int& a,
                                        const int& b) const override;
};


