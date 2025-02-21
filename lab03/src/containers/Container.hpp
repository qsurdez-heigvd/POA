#ifndef RIVER_CONTAINER_HPP
#define RIVER_CONTAINER_HPP

#include <list>
#include "../person/Person.hpp"
#include "../StateResult.hpp"

class Person;

class StateResult;

class Container {
public:

    /**
     * Constructor
     * @param name the name of the container
     */
    explicit Container(const std::string& name);

    /**
     * Check if the container contains a person
     * @param person the person to check
     * @return true if the person is in the container, false otherwise
     */
    [[nodiscard]] bool contains(const Person& person) const;


    /**
     * Find a person by its name
     * @param name the name of the person to find
     * @return the person if found, nullptr otherwise
     */
    [[nodiscard]] Person* findByName(const std::string& name) const;

    /**
     * Add a person to the container
     * @param person the person to add
     * @return the modified containero
     */
    Container& addPerson(Person* person);

    /**
     * Remove a person from the container
     * @param person the person to remove
     * @return the modified container
     */
    Container& removePerson(Person* person);

    /**
     * Check if the state of the container is valid, regarding the persons in it and their rules
     * @return a StateResult object containing the result of the check
     */
    virtual StateResult isContainerValid();

    /**
     * Get the number of persons in the container
     * @return the number of persons in the container
     */
    [[nodiscard]] size_t size() const;

    /**
     * Destructor
     */
    virtual ~Container() = default;

    /**
     * Clone the container
     * @return the cloned container
     */
    virtual Container* clone() = 0;

    /**
     * Display the passengers in the container
     */
    virtual void displayPassengers() const;

    /**
     * Display the container
     */
    void display() const;

    /**
     * Fonction qui permet de vider le container
     */
    void clear();
protected:

    std::list<Person*> getPassengers();

private:
    std::list<Person*> passengers;
    std::string name;
};


#endif //RIVER_CONTAINER_HPP
