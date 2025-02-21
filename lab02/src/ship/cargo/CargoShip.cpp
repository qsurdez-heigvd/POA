
#include "CargoShip.hpp"
#include "src/utils/ostreamUtils.hpp"

CargoShip::CargoShip(size_t _factoryNumber, long double _maxCargo, long double _currentCargo)
   : Ship(_factoryNumber), currentCargo(_currentCargo) {
   if (currentCargo > _maxCargo) {
      throw std::invalid_argument("Current Cargo cannot be bigger than maxCargo");
   }
}


std::ostream &CargoShip::formatToStream(std::ostream &os) const {
   Ship::formatToStream(os);
   ostreamUtils::printCargo(currentCargo, getMaxCargo(), os);
   return os;
}

long double CargoShip::getCurrentCargo() const {
   return currentCargo;
}

