/**
 * @file Implementation of the FieldStatsCalculator struct
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "FieldStatsCalculator.hpp"
#include <iostream>

double FieldStatsCalculator::simulate(size_t height, size_t width, size_t nbVampire,
                                      size_t nbHuman, size_t nbSimulations) {
   size_t successCount = 0;
   std::cout << "Stats are being calculated..." << std::endl;
   for (size_t i = 0; i < nbSimulations; ++i) {
      Field simulatingField(height, width, nbVampire, nbHuman);
      while (simulatingField.isFinished() == Status::RUNNING) {
         simulatingField.nextTurn();
      }
      if (simulatingField.isFinished() == Status::WIN) {
         successCount++;
      }
   }
   return static_cast<double>(successCount) / static_cast<double>(nbSimulations) * 100;
}
