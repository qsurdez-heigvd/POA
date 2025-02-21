/**
 * @file Implementation of the StarDreadnought class.
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
 */
#pragma once

#include "src/ship/cargo/CargoShip.hpp"

/**
 * @brief A class representing a star dreadnought. It is a specialization of the CargoShip class.
 */
class StarDreadnought : public CargoShip {
private:
   static size_t count;

public:

   /**
    * @inheritDoc
    */
   long double getWeight() const override;

   /**
    * @inheritDoc
    */
   unsigned long long int getSpeed() const override;

   /**
    * @inheritDoc
    */
   std::string getFactoryName() const override;

   /**
    * @inheritDoc
    */
   long double getMaxCargo() const override;

   /**
    * @brief Constructor of StarDreadnought
    * @param _currentCargo the current cargo amount
    */
   explicit StarDreadnought(long double _currentCargo);

};


