#ifndef RIVER_STATERESULT_HPP
#define RIVER_STATERESULT_HPP
#include <string>
#include <optional>
#include "person/Person.hpp"

/**
 * @file StateResult.hpp
 * @brief Definition of the StateResult class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class StateResult {
    bool state;
    std::optional<std::string> error;
public:

    /**
     * Constructor
     * @param state the state of the result
     * @param error the error message if the state is false, clear otherwise
     */
    StateResult(bool state, const std::string& error);

    /**
     * Constructor
     * @param state the state of the result
     */
    StateResult(bool state);

    /**
     * Tell if the result is valid
     * @return true if the result is valid, false otherwise
     */
    [[nodiscard]] bool isValid() const;

    /**
     * Get the error message
     * @return the error message if the state is false, "none" otherwise
     */
    std::string getError();
};

#endif //RIVER_STATERESULT_HPP
