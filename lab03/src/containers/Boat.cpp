#include "Boat.hpp"


const std::string& Boat::noDriver = "Aucun conducteur sur le bateau";
const std::string& Boat::tooManyPerson = "Déjà deux personnes sur le bateau";
Boat::Boat(const std::string& name, Bank *bank): Container(name), bank(bank){}

StateResult Boat::isContainerValid() {
    if(size() > 2) {
        return {false, tooManyPerson};
    }
    return Container::isContainerValid();
}

void Boat::setBank(Bank* bank) {
    this->bank = bank;
}

Bank* Boat::getBank() {
    return bank;
}

Container * Boat::clone() {
   return new Boat(*this);
}

void Boat::displayPassengers() const{
    std::cout << " <";
    Container::displayPassengers();
    std::cout << " >";
}

StateResult Boat::canMove()  {
    bool isDriverPresent = false;
    for(auto p : getPassengers()) {
        if(p->canDrive()) {
            isDriverPresent = true;
        }
    }
    if(!isDriverPresent) {
        return {false, noDriver};
    }
    return {true};
}

/*
Boat::Boat(const Boat &other) {
   if (this != &other) {
      this->bank = other.bank;
   }
}
*/



