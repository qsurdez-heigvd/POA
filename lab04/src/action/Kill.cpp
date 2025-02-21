/**
 * @file Implementation of the Kill class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Kill.hpp"
#include "../humanoids/Humanoid.hpp"

Kill::Kill(const std::shared_ptr<Humanoid>& target) : Action(target) {}

void Kill::execute(Field& field) {
   if (getHumanoid()->isAlive()) {
      getHumanoid()->kill(field);
   }
}
