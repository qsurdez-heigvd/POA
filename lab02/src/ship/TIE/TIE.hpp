/**
 * @file Implementation of the TIE class.
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
 */
#pragma once

#include "src/ship/TIE/TIEBaseModel.hpp"

class TIE : public TIEBaseModel {
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
    * @brief Constructor of TIE
    */
   TIE();

};


