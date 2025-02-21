
#include "Squadron.hpp"
#include "src/utils/ostreamUtils.hpp"

Squadron operator+(const Squadron &rhs, Ship &lhs) {
   return Squadron(rhs).addShip(lhs);
}

Squadron operator-(const Squadron &rhs, Ship &lhs) {
   return Squadron(rhs).deleteShip(lhs);
}

std::ostream &operator<<(std::ostream &os, const Squadron &squadron) {
   return squadron.formatToStream(os);
}

Squadron::Squadron(const std::string &_name) {
   initSquadron(_name);
}

Squadron::~Squadron() {
   deleteSquadron();
}

Squadron::Squadron(const Squadron &other) {
   initSquadron(other.name, other.chief);
   copySquadron(other);
}

Squadron::Squadron(Squadron &&other) noexcept {
   initSquadron(other.name);
   exchange(other);
}

Squadron &Squadron::operator=(const Squadron &other) {
   if (this != &other) {
      deleteSquadron();
      initSquadron(other.name, other.chief);
      copySquadron(other);
   }
   return *this;
}

Squadron &Squadron::operator=(Squadron &&other) noexcept {
   if (this != &other) {
      deleteSquadron();
      initSquadron(other.name);
      exchange(other);
   }
   return *this;
}

Squadron &Squadron::addShip(reference ship) {
   if (head != nullptr) {
      Node *current = head;
      while (current->next != nullptr) {
         if (current->next->value == &ship || current->value == &ship) {
            return *this;
         }
         current = current->next;
      }
      current->next = new Node{&ship, nullptr};
   } else {
      head = new Node{&ship, nullptr};
   }
   size++;
   return *this;
}

Squadron Squadron::addShipCopy(reference ship) const {
   return Squadron(*this).addShip(ship);
}

Squadron &Squadron::deleteShip(reference ship) {
   Node *current = head;
   while (current != nullptr) {
      if (current->value == &ship) {
         Node *toDelete = current;
         if (current->next != nullptr) {
            current->next = current->next->next;
         }
         if (toDelete->value == chief) {
            removeChief();
         }
         delete toDelete;
         if (toDelete == head) {
            head = nullptr;
         }
         size--;
         break;
      }
      current = current->next;
   }
   return *this;
}

Squadron Squadron::deleteShipCopy(reference ship) const {
   return Squadron(*this).deleteShip(ship);
}

Squadron &Squadron::operator+=(reference lhs) {
   return addShip(lhs);
}

Squadron &Squadron::operator-=(reference lhs) {
   return deleteShip(lhs);
}

void Squadron::setChief(reference newChief) {
   if (chief != nullptr || chief == &newChief) {
      return;
   }
   if (!contains(newChief)) {
      addShip(newChief);
   }
   chief = &newChief;
}

void Squadron::removeChief() {
   chief = nullptr;
}

Squadron::reference Squadron::get(size_t i) const {
   if (i >= size) {
      throw std::out_of_range("Index out of range");
   }
   Node *current = head;
   for (size_t j = 0; j < i; ++j) {
      current = current->next;
   }
   return *current->value;
}

void Squadron::setName(const std::string &newName) {
   name = newName;
}

bool Squadron::empty() const {
   return size == 0;
}

long double Squadron::fuelConsumption(long double distance, unsigned long long int speed) const {


   if (distance < 0 || speed <= 0) {
      throw std::invalid_argument("Distance and speed must be positive");
   }

   if (speed > getMaximumSpeed()) {
      throw std::invalid_argument("Speed cannot be higher than the maximum speed at which the squadron travel");
   }

   if (empty()) {
      throw std::runtime_error("Squadron is empty");
   }

   long double totalFuel = 0;
   Node *current = head;
   for (size_t i = 0; i < size; i++) {
      totalFuel += current->value->fuelConsumption(distance, speed);
      current = current->next;
   }
   return totalFuel;
}

unsigned long long int Squadron::getMaximumSpeed() const {
   unsigned long long minSpeed = std::numeric_limits<unsigned long long>::max();
   Node *current = head;
   while (current != nullptr) {
      minSpeed = std::min(minSpeed, current->value->getSpeed());
      current = current->next;
   }
   return minSpeed;
}

long double Squadron::getWeight() const {
   long double totalWeight = 0.0;
   Node *current = head;
   while (current != nullptr) {
      totalWeight += current->value->getWeight();
      current = current->next;
   }
   return totalWeight;
}

std::ostream &Squadron::formatToStream(std::ostream &os) const {
   if (!empty()) {
      os << "Squadron " << name << "\n";
      ostreamUtils::printSpeed(getMaximumSpeed(), os);
      ostreamUtils::printWeight(getWeight(), os);
      if (chief != nullptr) {
         os << "--Leader:\n" << *chief;
      }
      if (head->value == chief && head->next != nullptr || head->value != chief) {
         os << "--Members:\n";
         Node *current = head;
         while (current != nullptr) {
            if (current->value == chief) {
               current = current->next;
               continue;
            }
            os << *current->value;
            current = current->next;
         }
      }
   } else {
      os << "Squadron is empty\n";
   }
   return os;
}

// Private methods

void Squadron::initSquadron(const std::string &n, pointer _chief) {
   chief = _chief;
   name = n;
}


void Squadron::deleteSquadron() {
   Node *current = head;
   while (current != nullptr) {
      Node *next = current->next;
      delete current;
      current = next;
   }
}

void Squadron::copySquadron(const Squadron &other) {
   if (head == other.head) {
      return;
   }
   for (size_t i = 0; i < other.size; i++) {
      addShip(other.get(i));
   }
}

void Squadron::exchange(Squadron &other) {
   head = std::exchange(other.head, nullptr);
   name = std::exchange(other.name, std::string{});
   chief = std::exchange(other.chief, nullptr);
   size = std::exchange(other.size, 0);
}

bool Squadron::contains(Squadron::reference ship) {
   Node *current = head;
   while (current != nullptr) {
      if (current->value == &ship) {
         return true;
      }
      current = current->next;
   }
   return false;
}
