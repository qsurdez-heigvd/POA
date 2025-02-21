/**
 * @file Declaration of the Kill class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include "Action.hpp"

/**
 * Kill class to represent the action of killing a humanoid.
 * It inherits from the Action class. It is used to kill a humanoid.
 */
class Kill : public Action {

public:

    /**
     * Constructor of the class Kill representing the action of killing
     * @param target the humanoid that will be killed
     */
    explicit Kill(const std::shared_ptr<Humanoid>& target);

    /**
     * Execute the Kill action
     * @param field current field
     */
    void execute(Field& field) override;

};


