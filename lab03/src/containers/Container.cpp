#include "Container.hpp"
#include <algorithm>
#include <iostream>

Container::Container(const std::string& name): name(name){

}


bool Container::contains(const Person& person) const {

    return std::find(passengers.begin(), passengers.end(), &person) != passengers.end();
}

Person* Container::findByName(const std::string& name) const {
   auto p = std::find_if(passengers.begin(), passengers.end(),  [name](Person* person) {
      return person->getName() == name;
   });

   return p == passengers.end() ? nullptr : *p;
}

Container& Container::addPerson(Person* person) {
    passengers.emplace_back(person);
    return *this;
}

Container& Container::removePerson(Person* person) {
    passengers.remove(person);
    return *this;
}

StateResult Container::isContainerValid() {
    for(auto p : passengers) {
        const StateResult& a = p->isStateValid(*this);
        if(!a.isValid()) {
            return a;
        }
    }
    return {true};
}

std::list<Person*> Container::getPassengers() {
    return passengers;
}

size_t Container::size() const {
    return passengers.size();
}

void Container::displayPassengers() const{
   for(auto person: passengers){
      std::cout << " " + person->getName();
   }
}

void Container::display() const {
    std::cout << name << ":";
    displayPassengers();
    std:: cout << "\n";
}

void Container::clear() {
  passengers.clear();
}






