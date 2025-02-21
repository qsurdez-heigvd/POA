/**
 * @file Declaration of the Move class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include "Action.hpp"
#include "../utils/Vec2D.hpp"
#include <vector>
#include <optional>

class Vec2D;

/**
 * Move class to represent the action of moving a humanoid.
 */
class Move : public Action {

public:

   /**
    * Method to execute the Move action
    * @param field the current field
    */
    void execute(Field& field) override;

    /**
     * Constructor of the class Move representing the action of moving
     * @param range the range of the movement
     * @param mover the humanoid that will move
     * @param target the humanoid that will be moved
     */
    Move(size_t range, const std::shared_ptr<Humanoid>& mover, std::optional<Vec2D> target = std::nullopt);


private:
    size_t range_;
    std::optional<Vec2D> target_;

    /**
     * Method to get the possible positions for the humanoid to move
     * @param position the present position of the humanoid
     * @param field the current field
     * @return vector of all possible positions
     */
   static std::vector<Vec2D> getPossiblePositions(const Vec2D &position, const Field &field);
};



