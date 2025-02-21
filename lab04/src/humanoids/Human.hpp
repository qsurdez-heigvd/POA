/**
 * @file Declaration of the Human class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <string>
#include <vector>
#include "Humanoid.hpp"

/**
 * Class representing a human in the game. It inherits from the Humanoid class.
 * Its behavior is simple, it moves 1 unit at a time in a random direction and can be killed.
 */
class Human : public Humanoid {
public:

   /**
    * Constructor of the Human class
    * @param position the starting position of the human
    */
   explicit Human(const Vec2D &position);

   /**
    * Getter for the displayer to know what's the type of the object
    * @return the string representing the object type
    */
   std::string getType() override;

   /**
    * Method that will choose the next action of the human depending on its environment
    * @param field the current field
    * @return the next action the human will execute
    */
   std::unique_ptr<Action> chooseAction(const Field &field) override;

   /**
    * Method to kill the humanoid and decrement the number of humans currently in the game
    * @param field the current field
    */
   void kill(Field &field) override;
};



