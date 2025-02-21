/**
 * @file Implementation of the Buffy class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Buffy.hpp"
#include "Vampire.hpp"
#include "../action/Kill.hpp"
#include "../action/Move.hpp"
#include "../field/Field.hpp"

Buffy::Buffy(const Vec2D& position) : Humanoid(position) {}

std::unique_ptr<Action> Buffy::chooseAction(const Field& field) {
   if (!field.aliveVampires()) {
      // Move like a human
      return std::make_unique<Move>(Humanoid::getActionRange(), shared_from_this());
   }

   auto closest = field.findClosestHumanoid<Vampire>(shared_from_this());
   size_t distanceToClosestVampire = this->getPosition().calculateDistance(closest->getPosition());
   if (distanceToClosestVampire <= 1) {
      return std::make_unique<Kill>(closest);
   }
   return std::make_unique<Move>(getActionRange(), shared_from_this(), closest->getPosition());
}

size_t Buffy::getActionRange() const {
   return 2;
}

std::string Buffy::getType() {
   return "B";
}

void Buffy::kill(Field &field) {
   // Buffy cannot die
}