#pragma once

#include <cstddef>

/**
 * @brief The Operation class represents a generic arithmetic operation.
 */
class Operation {
public:
   /**
    * @brief Destructor for Operation.
    */
   virtual ~Operation() = default;

   /**
    * @brief Calculates the result of the operation.
    * @param a The first operand.
    * @param b The second operand.
    * @return The result of the operation.
    */
   [[nodiscard]] virtual int calculate(const int& a,
                                                const int& b) const = 0;

protected:
   /**
    * @brief Default constructor for Operation.
    */
   Operation() = default;
};




