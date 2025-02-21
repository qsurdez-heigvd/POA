#ifndef RIVER_INDEPENDENTPERSON_HPP
#define RIVER_INDEPENDENTPERSON_HPP
#include "Person.hpp"

/**
 * @file IndependentPerson.hpp
 * @brief Definition of the IndependentPerson class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class IndependentPerson : public Person {
public:

    /**
     * Constructor
     * @param name the name of the independent person
     */
    explicit IndependentPerson(const std::string& name);

    /**
     * Tell if a person is able to drive a boat
     * @return true if the person can drive, false otherwise
     */
    [[nodiscard]] bool canDrive() const override;

    /**
     * Tell if a person can be with the other persons in a container
     * @param container the container to check
     * @return a StateResult object containing the result of the check
     */
    StateResult isStateValid(const Container& container) override;
};


#endif //RIVER_INDEPENDENTPERSON_HPP
