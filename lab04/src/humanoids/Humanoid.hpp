/**
 * @file Declaration of the Humanoid class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <string>
#include "../utils/Vec2D.hpp"
#include "../action/Action.hpp"


class Field;

/**
 * Humanoid abstract class representing a humanoid
 */
class Humanoid : public std::enable_shared_from_this <Humanoid> {
public:
    /**
     * Constructor of the class
     * @param position at which it will be created
     */
    explicit Humanoid(const Vec2D& position);

    /**
     * Default destructor
     */
    virtual ~Humanoid() = default;

    /**
     * Purely abstract method to get the next action of the humanoid
     * @param field the current currentField
     * @return a pointer to the action created
     */
    virtual std::unique_ptr<Action> chooseAction(const Field& field) = 0;

    /**
     * Setter for the nextAction attribute
     * @param field the current currentField
     */
    virtual void setAction(const Field& field);

    /**
     * Method to execute the action on the currentField
     * @param field the current currentField
     */
    virtual void executeAction(Field& field);

    /**
     * Getter for the imAlive attribute
     * @return the value of imAlive
     */
    bool isAlive() const;

    /**
     * Method to get the string corresponding to each humanoid
     * @return the string representation of the humanoid
     */
    virtual std::string getType() = 0;

    /**
     * Getter for the position attribute
     * @return the position attribute
     */
    Vec2D getPosition() const;

    /**
     * Setter for the position attribute
     * @param newPos the new value of the position attribute
     */
    void setPosition(const Vec2D& newPos);

    /**
     * Method to kill the humanoid
     */
    virtual void kill(Field& field);

    /**
     * Abstract method for the range of movement each humanoid has
     * @return the range for movement
     */
    virtual size_t getActionRange() const;

private:
    std::unique_ptr<Action> nextAction;
    Vec2D position_;
    bool imAlive;
};

