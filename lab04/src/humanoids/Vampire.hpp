/**
 * @file Declaration of the Vampire class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include "Humanoid.hpp"

/**
 * Class representing a vampire in the game. It inherits from the Humanoid class.
 * It will move 1 unit at a time towards the closest human.
 * It can kill humans at a range of 1.
 */
class Vampire : public Humanoid {

public:

   /**
    * Constructor of the Vampire class
    * @param position the starting position of the object
    */
   explicit Vampire(const Vec2D &position);

   /**
    * Getter for the displayer to know what's the type of the object
    * @return the string representing the object type
    */
   std::string getType() override;

   /**
    * Method that will choose the next action of the vampire depending on its environment
    * @param field the current field
    * @return the next action the object will execute
    */
   std::unique_ptr<Action> chooseAction(const Field &field) override;

   /**
    * Method to kill the vampire. It will also decrement the number of vampires currently in the game
    * @param field the current field
    */
   void kill(Field &field) override;
};
