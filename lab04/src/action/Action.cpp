/**
 * @file Implementation of the Action class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Action.hpp"

Action::Action(const std::shared_ptr<Humanoid>& humanoid) : humanoid_(humanoid) {}

std::shared_ptr<Humanoid> Action::getHumanoid() const {
   return humanoid_.lock();
}
