/**
 * @file IndependentPerson.cpp
 * @brief Implementation of the IndependentPerson class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "IndependentPerson.hpp"

IndependentPerson::IndependentPerson(const std::string& name) : Person(name) {

}

bool IndependentPerson::canDrive() const {
    return true;
}

StateResult IndependentPerson::isStateValid(const Container& container) {
    return {true};
}
