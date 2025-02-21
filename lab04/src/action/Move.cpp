/**
 * @file Implementation of the Move class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */


#include <iostream>
#include "Move.hpp"
#include "../humanoids/Humanoid.hpp"
#include "../field/Field.hpp"
#include "../utils/Random.hpp"

Move::Move(size_t range, const std::shared_ptr<Humanoid>& mover, std::optional<Vec2D> target)
        : Action(mover), range_(range), target_(target) {}

void Move::execute(Field& field) {

   std::shared_ptr<Humanoid> mover = getHumanoid();

   if (mover == nullptr) {
      return;
   }

   Vec2D newPosition = mover->getPosition();
   Vec2D direction;

   for (size_t i = 0; i < range_; i++) {
      if (auto target = target_) {
         direction = newPosition.getDirection(target.value());
      } else {
         std::vector<Vec2D> directions = Move::getPossiblePositions(newPosition, field);

         if (directions.empty()) {
            break;
         }

         direction = directions.at(Random::generateFrom0(static_cast<int>(directions.size() - 1)));
      }
      newPosition = newPosition.addition(direction);
   }

   mover->setPosition(newPosition);
}

std::vector<Vec2D> Move::getPossiblePositions(const Vec2D &position, const Field &field) {
   std::vector<Vec2D> nextPositions{};
   nextPositions.reserve(8);

   int maxX = static_cast<int>(field.getWidth());
   int maxY = static_cast<int>(field.getHeight());
   for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
         if (i == 0 && j == 0) {
            continue;
         }

         int x = position.x + i;
         int y = position.y + j;

         if (x < 0 || x >= maxX || y < 0 || y >= maxY) {
            continue;
         }

         nextPositions.emplace_back(i, j);
      }
   }

   return nextPositions;
}
