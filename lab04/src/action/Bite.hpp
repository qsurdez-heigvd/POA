/**
 * @file Declaration of the Bite class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include "Kill.hpp"

/**
 * Bite class to represent the action of biting a humanoid.
 * It inherits from the Kill class as the action executed
 * with a bite can be either a Kill or a transformation into a Vampire.
 */
class Bite : public Kill {
public:
    /**
     * Constructor of the class Bite representing the action of biting
     * @param hunter the humanoid that will bite
     */
   explicit Bite(const std::shared_ptr<Humanoid>& target);

   /**
    * Execute the bite action
    * @param field the current field
    */
   void execute(Field &field) override;
};
