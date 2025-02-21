/**
 * @file Implementation of the Bite class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */



#include "Bite.hpp"
#include "../humanoids/Humanoid.hpp"
#include "../field/Field.hpp"
#include "../utils/Random.hpp"
#include "../humanoids/Vampire.hpp"
#include "Kill.hpp"


Bite::Bite(const std::shared_ptr<Humanoid> &target) : Kill(target) {}

void Bite::execute(Field &field) {
   const auto &humanoid = getHumanoid();
   if (humanoid->isAlive()) {
      if (Random::randomBool()) {
         field.addHumanoid(std::make_shared<Vampire>(humanoid->getPosition()));
         field.vampireBorn();
      }
      Kill::execute(field);
   }
}

