/**
 * @file StateResult.cpp
 * @brief Implementation of the StateResult class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include "StateResult.hpp"

StateResult::StateResult(bool state, const std::string& error) : state(state), error(error) {

}

StateResult::StateResult(bool state) : StateResult(state, "") {
}

bool StateResult::isValid() const {
    return state;
}

std::string StateResult::getError() {
    return error.value_or("none");
}
