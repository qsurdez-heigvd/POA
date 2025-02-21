/**
 * @file Implementation of the Random class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Humanoid.hpp"

Humanoid::Humanoid(const Vec2D& position) : position_(position), imAlive(true) {}

bool Humanoid::isAlive() const {
   return imAlive;
}

Vec2D Humanoid::getPosition() const {
   return position_;
}

void Humanoid::setAction(const Field& field) {
   nextAction = chooseAction(field);
}

void Humanoid::executeAction(Field& field) {
   if (nextAction) {
      nextAction->execute(field);
      nextAction.reset();
   }
}

void Humanoid::kill(Field& field) {
   imAlive = false;
}

void Humanoid::setPosition(const Vec2D& newPos) {
   position_ = newPos;
}

size_t Humanoid::getActionRange() const {
   return 1;
}




