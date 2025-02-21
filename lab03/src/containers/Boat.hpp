#ifndef RIVER_BOAT_HPP
#define RIVER_BOAT_HPP

#include <list>
#include <iostream>
#include "Container.hpp"
#include "../person/Person.hpp"
#include "Bank.hpp"
#include "../StateResult.hpp"

class Boat : public Container {

public:

    /**
     * Constructor
     * @param name the name of the boat
     * @param bank the bank on which the boat is
     */
    Boat(const std::string& name, Bank* bank);

    /**
     * Set the bank where the boat is located
     * @param bank the bank
     */
    void setBank(Bank* bank);

    /**
     * Get the bank where the boat is located
     * @return the bank
     */
    Bank* getBank();

    /**
     * Clone the boat
     * @return the cloned boat
     */
    Container* clone() override;

    /**
     * Display the passengers of the boat
     */
    void displayPassengers() const override;

    /**
     * Check if there is a driver on board
     * @return The status of the move as a StateResult
     */
    StateResult canMove();

private:
    Bank* bank; // ptr because can be nullptr
    StateResult isContainerValid() override;
    static const std::string& noDriver;
    static const std::string& tooManyPerson;

};

#endif //RIVER_BOAT_HPP
