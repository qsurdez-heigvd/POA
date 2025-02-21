
#include "TIEInterceptor.hpp"

size_t TIEInterceptor::count = 1;

TIEInterceptor::TIEInterceptor() : TIEBaseModel(count++) {

}

unsigned long long int TIEInterceptor::getSpeed() const {
   return 110;
}

long double TIEInterceptor::getWeight() const {
   return 5;
}

std::string TIEInterceptor::getFactoryName() const {
   return TIEBaseModel::getFactoryName() + "IN";
}
