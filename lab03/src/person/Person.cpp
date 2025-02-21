/**
 * @file Person.cpp
 * @brief Implementation of the Person class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Person.hpp"

#include <utility>

Person::Person(const std::string& name) : name(name){}

std::string Person::getName() const{
    return name;
}
