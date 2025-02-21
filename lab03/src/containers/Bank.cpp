#include "Bank.hpp"

Bank::Bank(const std::string& name): Container(name){}

Container* Bank::clone() {
   return new Bank(*this);
}