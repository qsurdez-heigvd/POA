/**
 * @file Implementation of the findClosestHumanoid function
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <numeric>

/**
 * Method to find the closest humanoid of type T from the hunter.
 * @tparam T the type of the humanoid we want to find
 * @param hunter the humanoid looking for another humanoid
 * @return the closest humanoid of type T from the hunter
 */
template<typename T>
std::shared_ptr<T> Field::findClosestHumanoid(const std::shared_ptr<Humanoid>& hunter) const {
   std::shared_ptr<T> closest;
   size_t minDistance = width_ * height_;
   for (const auto& humanoid: humanoids) {
      if (dynamic_cast<T*>(humanoid.get())) {
         size_t distance = hunter->getPosition().calculateDistance(humanoid->getPosition());
         if (distance < minDistance) {
            minDistance = distance;
            closest = std::dynamic_pointer_cast<T>(humanoid);
         }
      }
   }
   return closest;
}
