/**
 * @file Girl.cpp
 * @brief Implementation of the Girl class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "Girl.hpp"

const std::string& Girl::girlWithFather = "La fille ne peut pas être seule avec son père";
Girl::Girl(const std::string& name, Person* father, Person* mother): Kid(name, father, mother){

}

StateResult Girl::isStateValid(const Container& container) {
    if(!isDependencyRespected(getMother(), getFather(), container)) {
        return {false, girlWithFather};
    }

    return {true };
}
