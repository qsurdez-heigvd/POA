#ifndef RIVER_KID_HPP
#define RIVER_KID_HPP

#include "Person.hpp"
#include "../StateResult.hpp"

/**
 * @file Kid.hpp
 * @brief Definition of the Kid class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class Kid : public Person {
public:
    /**
     * Constructor
     * @param name the name of the kid
     * @param father the father of the kid
     * @param mother the mother of the kid
     */
    Kid(const std::string& name, Person* father, Person* mother);
public:
    /**
     * Get the father of the kid
     * @return the father of the kid
     */
    [[nodiscard]] Person* getFather() const;

    /**
     * Get the mother of the kid
     * @return the mother of the kid
     */
    [[nodiscard]] Person* getMother() const;

    /**
     * Tell if a kid can drive
     * @return true if the kid can drive, false otherwise
     */
    [[nodiscard]] bool canDrive() const override;

    /**
     * Tell if a kid can be with the other people in a container
     * @param dependsOn the person the kid depends on
     * @param notAloneWith the person the kid can't be alone with
     * @param container the container to check
     * @return a StateResult object containing the result of the check
     */
    bool isDependencyRespected(Person* dependsOn, Person* notAloneWith, const Container& container) const;

private:
    Person* father;
    Person* mother;
};


#endif //RIVER_KID_HPP
