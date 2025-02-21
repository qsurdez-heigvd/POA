#ifndef RIVER_THIEF_HPP
#define RIVER_THIEF_HPP


#include "Person.hpp"
#include "../StateResult.hpp"

/**
 * @file Thief.hpp
 * @brief Definition of the Thief class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class Thief : public Person {
public:

    /**
     * Constructor
     * @param name the name of the thief
     * @param policeman the policeman to which the thief is associated
     */
    Thief(const std::string& name, Person* policeman);
private:
    Person* policeman;
    static const std::string& thiefWithoutPoliceman;

    /**
     * Tell if a thief can drive
     * @return true if the thief can drive, false otherwise
     */
    bool canDrive() const override;

    /**
     * Tell if a thief can be with the other people in a container
     * @param container the container to check
     * @return a StateResult object containing the result of the check
     */
    StateResult isStateValid(const Container &container) override;
};


#endif //RIVER_THIEF_HPP
