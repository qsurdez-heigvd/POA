
#include <iomanip>
#include "ostreamUtils.hpp"

std::ostream &ostreamUtils::printWeight(long double weight, std::ostream &os) {
   fixed(os);
   os << std::setprecision(2) << "weight: " << weight << " tons\n";
   return os;
}

std::ostream &ostreamUtils::printSpeed(unsigned long long speed, std::ostream &os) {
   os << "max speed: " << speed << " MGLT\n";
   return os;
}

std::ostream &ostreamUtils::printCargo(long double currentCargo, long double maxCargo, std::ostream &os) {
   fixed(os);
   os << std::setprecision(1) << "cargo: " << currentCargo << " tons ( max : " << maxCargo << ")\n";
   return os;
}

std::ostream &ostreamUtils::fixed(std::ostream &os) {
   os << std::fixed;
   return os;
}