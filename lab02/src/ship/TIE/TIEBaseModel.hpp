/**
 * @file Implementation of the TIEBaseModel class.
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
 */
#pragma once

#include "src/ship/Ship.hpp"


/**
 * @brief A class representing a TIE base model.
 */
class TIEBaseModel : public Ship {
protected:
   /**
    * @brief Constructor for the TIEBaseModel class
    * @param _factoryNumber the factory number of the ship
    */
   explicit TIEBaseModel(size_t _factoryNumber);

public:

   /**
    * @inheritDoc
    */
   std::string getFactoryName() const override;

};



