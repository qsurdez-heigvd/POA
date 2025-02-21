/**
 * @file Kid.cpp
 * @brief Implementation of the Kid class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Kid.hpp"

Kid::Kid(const std::string& name, Person* father, Person* mother): Person(name), father(father), mother(mother){

}

bool Kid::canDrive() const {
    return false;
}

bool Kid::isDependencyRespected(Person* dependsOn, Person* notAloneWith, const Container& container) const {
    if(container.contains(*notAloneWith) && !container.contains(*dependsOn)) {
        return false;
    }
    return true;
}

Person* Kid::getFather() const {
    return father;
}

Person* Kid::getMother() const {
    return mother;
}



