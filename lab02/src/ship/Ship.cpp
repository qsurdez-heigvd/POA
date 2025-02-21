
#include "Ship.hpp"
#include "src/utils/ostreamUtils.hpp"

#include <utility>
#include <cmath>

Ship::Ship(size_t _factoryNumber) : factoryNumber(_factoryNumber) {}

void Ship::setNickName(const std::string &_nickName) {
   this->nickName = _nickName;
}

std::ostream &operator<<(std::ostream &os, const Ship &ship) {
   return ship.formatToStream(os);
}

std::ostream &Ship::formatToStream(std::ostream &os) const {
   os << (nickName ? nickName.value() + " " : "")
   << "[" <<  getFactoryName() << " #" << factoryNumber << "]""\n";
   ostreamUtils::printWeight(getWeight(), os);
   ostreamUtils::printSpeed(getSpeed(), os);
   return os;
}

long double Ship::fuelConsumption(long double distance, unsigned long long speed) const {
   return std::cbrtl(distance) / 2.0 * log10l(getWeight() * static_cast<long double>(speed)) * log10l(distance + 1.0);
}

size_t Ship::getFactoryNumber() const {
   return factoryNumber;
}