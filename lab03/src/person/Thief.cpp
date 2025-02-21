/**
 * @file Thief.cpp
 * @brief Implementation of the Thief class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Thief.hpp"

const std::string& Thief::thiefWithoutPoliceman = "Le voleur doit avoir son policier pour être avec d'autres personnes";

Thief::Thief(const std::string& name, Person* policeman) : Person(name), policeman(policeman) {

}

bool Thief::canDrive() const{
    return false;
}

StateResult Thief::isStateValid(const Container& container) {
    if (!container.contains(*policeman) && container.size() > 1) {
        return {false, thiefWithoutPoliceman};
    }
    return {true};
}
