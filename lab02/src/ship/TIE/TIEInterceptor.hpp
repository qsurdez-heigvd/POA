/**
 * @file Implementation of the TIEInterceptor class.
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
 */
#pragma once

#include "src/ship/TIE/TIEBaseModel.hpp"

class TIEInterceptor : public TIEBaseModel {

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
    * @brief Constructor of TIEInterceptor
    */
   TIEInterceptor();

};



