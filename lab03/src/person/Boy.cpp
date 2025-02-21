/**
 * @file Boy.cpp
 * @brief Implementation of the Boy class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Boy.hpp"

const std::string& Boy::boyWithMother = "Le garçon ne peut pas être seul avec sa mère";

Boy::Boy(const std::string& name, Person* father, Person* mother): Kid(name, father, mother){

}

StateResult Boy::isStateValid(const Container& container) {
    if(!isDependencyRespected(getFather(), getMother(), container)) {
        return {false, boyWithMother};
    }

    return {true };
}
