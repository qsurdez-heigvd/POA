/**
 * @file Implementation of the CargoShip class.
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
 */
#pragma once

#include "src/ship/Ship.hpp"

/**
 * @brief Abstract class representing a specialization of Ship that can carry cargo.
 * they have a cargo capacity and a current cargo amount.
 */
class CargoShip : public Ship {
private:
   long double currentCargo;

protected:

   /**
    * @brief Constructor of CargoShip
    * @throw std::invalid_argument if the current cargo is bigger than the max cargo
    * @param _factoryNumber the factory number of the ship
    * @param _maxCargo the max cargo capacity
    * @param _currentCargo the current cargo amount
    */
   explicit CargoShip(size_t _factoryNumber, long double _maxCargo, long double _currentCargo);

public:

   /**
    * @brief Get the max cargo capacity
    * @return the max cargo capacity
    */
   virtual long double getMaxCargo() const = 0;

   /**
    * @brief Get the current cargo amount.
    * @return the current cargo amount.
    */
   long double getCurrentCargo() const;

   /**
    * @inheritDoc
    */
   std::ostream &formatToStream(std::ostream &os) const override;

};



