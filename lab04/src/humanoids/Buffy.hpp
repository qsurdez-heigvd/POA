/**
 * @file Declaration of the Buffy class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include "Humanoid.hpp"
#include <string>

/**
 * Class to reprensent the hunteress Buffy. It inherits from Humanoid and will override its function.
 * Buffy is super speedy and can move 2 units at a time. She can only kill at a range of 1
 */
class Buffy : public Humanoid {
private:

public:

   /**
    * Constructor of the Buffy class
    * @param position starting position of the object
    */
    explicit Buffy(const Vec2D& position);

    /**
     * Method that will choose the next action of Buffy depending on its environment
     * @param field the current field
     * @return the next action the object will execute
     */
     std::unique_ptr<Action> chooseAction(const Field& field) override;

     /**
      * Method to get the range of the action Buffy
      * @return
      */
    size_t getActionRange() const override;

    /**
     * Getter for the displayer to know what's the type of the object
     * @return the string representing the object type
     */
    std::string getType() override;

    /**
     * Method overriding the kill method of the Humanoid class. Buffy can't be killed.
     * She's a superwoman
     * @param field the current field
     */
    void kill(Field& field) override;
};


