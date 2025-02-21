/**
 * @file Declaration of the Action class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <memory>

class Field;

class Humanoid;

/**
 * Action class to represent the action made by a humanoid
 */
class Action {

public:
    /**
     * Constructor of the class
     * @param humanoid the humanoid that will execute the action
     */
    explicit Action(const std::shared_ptr<Humanoid>& humanoid);

    /**
     * Default destructor of the class
     */
    virtual ~Action() = default;

    /**
     * Preventing the copy of an action
     */
    Action(const Action&) = delete;

    /**
     * Preventing the copy of an action
     */
    Action& operator=(const Action&) = delete;

    /**
     * Purely virtual method to execute the action
     * @param field the current field
     */
    virtual void execute(Field& field) = 0;

    /**
     * Getter for the humanoid_ attribute
     * @return the humanoid_ attribute
     */
    [[nodiscard]] std::shared_ptr<Humanoid> getHumanoid() const;

private:
    std::weak_ptr<Humanoid> humanoid_;
};
