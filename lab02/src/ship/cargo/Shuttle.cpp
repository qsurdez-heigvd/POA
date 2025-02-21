#include "Shuttle.hpp"

size_t Shuttle::count = 1;


Shuttle::Shuttle(long double currentCargo) : CargoShip(count++, getMaxCargo(), currentCargo) {
}

long double Shuttle::getWeight() const {
   return 360.0 + getCurrentCargo();
}

std::string Shuttle::getFactoryName() const {
   return "Lambda-class shuttle";
}

unsigned long long int Shuttle::getSpeed() const {
   return 54.0;
}

long double Shuttle::getMaxCargo() const {
   return 80.0;
}
