/**
 * @file Implementation of the Vampire class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */


#include "Vampire.hpp"
#include "Human.hpp"
#include "../action/Kill.hpp"
#include "../action/Bite.hpp"
#include "../action/Move.hpp"
#include "../field/Field.hpp"

Vampire::Vampire(const Vec2D& position) : Humanoid(position) {}

std::string Vampire::getType() {
   return "v";
}

std::unique_ptr<Action> Vampire::chooseAction(const Field& field) {
   if (!field.aliveHumans()) {
      return nullptr;
   }
   auto closestHuman = field.findClosestHumanoid<Human>(shared_from_this());
   size_t distanceToClosestHuman = this->getPosition().calculateDistance(closestHuman->getPosition());
   if(distanceToClosestHuman > getActionRange()) {
      return std::make_unique<Move>(getActionRange(), shared_from_this(), closestHuman->getPosition());
   }
   return std::make_unique<Bite>(closestHuman);
}

void Vampire::kill(Field& field) {
   Humanoid::kill(field);
   field.vampireKilled();
}







