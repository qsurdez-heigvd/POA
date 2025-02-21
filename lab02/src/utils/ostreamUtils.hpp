/**
 * @file Implementation of the namespace ostreamUtils
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
*/
#pragma once

#include <ostream>

/**
 * @brief A namespace containing functions to print information
 */
namespace ostreamUtils {

   /**
    * @brief Print the weight with specific precision of 2
    * @param weight the weight to print
    * @param os the output stream
    * @return the changed output stream
    */
   std::ostream &printWeight(long double weight, std::ostream &os);

   /**
    * @brief Print the speed with specific precision of 0
    * @param speed the speed to print
    * @param os the output stream
    * @return the changed output stream
    */
   std::ostream &printSpeed(unsigned long long speed, std::ostream &os);

   /**
    * @brief Print the current cargo and the max cargo with specific precision of 1
    * @param currentCargo the current cargo to print
    * @param maxCargo the max cargo to print
    * @param os the output stream
    * @return the changed output stream
    */
   std::ostream &printCargo(long double currentCargo, long double maxCargo, std::ostream &os);

   /**
    * @brief Set the output stream to fixed
    * @param os the output stream
    * @return the changed output stream
    */
   std::ostream &fixed(std::ostream &os);

}

