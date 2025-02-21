
#include "TIE.hpp"

size_t TIE::count = 1;

TIE::TIE() : TIEBaseModel(count++) {

}

long double TIE::getWeight() const {
   return 6.0;
}

unsigned long long int TIE::getSpeed() const {
   return 100;
}

std::string TIE::getFactoryName() const {
   return TIEBaseModel::getFactoryName() + "LN";
}
