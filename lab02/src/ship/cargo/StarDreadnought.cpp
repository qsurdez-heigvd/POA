#include "StarDreadnought.hpp"

size_t StarDreadnought::count = 1;

StarDreadnought::StarDreadnought(long double _currentCargo) : CargoShip(count++, getMaxCargo(), _currentCargo) {

}

long double StarDreadnought::getWeight() const {
   return 9e9 + getCurrentCargo();
}

unsigned long long int StarDreadnought::getSpeed() const {
   return 40;
}

std::string StarDreadnought::getFactoryName() const {
   return "Super-class Star Destroyer";
}

long double StarDreadnought::getMaxCargo() const {
   return 250e3;
}

