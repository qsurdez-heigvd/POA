#ifndef RIVER_PERSON_HPP
#define RIVER_PERSON_HPP

#include <string>
#include "../StateResult.hpp"
#include "../containers/Container.hpp"
class Container;

/**
 * @file Person.hpp
 * @brief Definition of the Person class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class Person {
public:

    /**
     * Constructor
     * @param name the name of the person
     */
    explicit Person(const std::string& name);

    /**
     * Destructor
     */
    virtual ~Person() = default;

    /**
     * Tell if a person is able to drive a boat
     * @return true if the person can drive, false otherwise
     */
    [[nodiscard]] virtual bool canDrive() const = 0;

    /**
     * Tell if a person can be with the other persons in a container
     * @param container the container to check
     * @return a StateResult object containing the result of the check
     */
    virtual StateResult isStateValid(const Container& container) = 0;

    /**
     * Get the name of the person
     * @return the name of the person
     */
    [[nodiscard]] std::string getName() const;
private:
    std::string name;
};


#endif //RIVER_PERSON_HPP
