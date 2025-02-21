/**
 * @file Implementation of the Human class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Human.hpp"
#include "../action/Move.hpp"
#include "../field/Field.hpp"

Human::Human(const Vec2D& position) : Humanoid(position) {}

std::unique_ptr<Action> Human::chooseAction(const Field& field) {
   return std::make_unique<Move>(getActionRange(), shared_from_this());
}

std::string Human::getType() {
   return "h";
}

void Human::kill(Field& field) {
   Humanoid::kill(field);
   field.humanKilled();
}
