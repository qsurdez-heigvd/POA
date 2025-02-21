#ifndef RIVER_CONTROLLER_HPP
#define RIVER_CONTROLLER_HPP

#include "containers/Bank.hpp"
#include "containers/Boat.hpp"
#include "person/IndependentPerson.hpp"
#include <map>
#include <functional>

/**
 * @file Controller.hpp
 * @brief Definition of the Controller class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class Controller {
private:
    StateResult lastState;
    std::list<Person*> persons;
    int turn;
    Bank* leftBank;
    Bank* rightBank;
    Boat* boat;
    struct CommandDescription {
        std::string description;
        std::function<void(Controller&, const std::string&)> function;
    };
    static const std::map<std::string, CommandDescription> COMMANDS;
    static const std::string BANK;
    static const std::string RIVER;
    bool running;

public:

    /**
     * Constructor
     */
    Controller();

    /**
     * Destructor
     */
    ~Controller();

    /**
     * Display the menu with the different commands offered to the user
     */
    void showMenu() const;

    /**
     * Display the current state of the game, show the persons on the banks and the boat
     */
    void display() const;

    /**
     * Display the initial state of the game (i.e. menu and initial state)
     */
    void displayInitialSituation() const;

    /**
     * Unfold the next iteration
     */
    void nextTurn();

    bool checkMove();

    /**
     * Quit the game
     */
    void quit();

    /**
     * Reset the game
     */
    void reset();

    /**
     * Move a person from one bank to the other
     * @param person the person to move
     */
    void movePerson(std::string person, Container& from, Container& to);

    /**
     * Embark a person on the boat
     * @param name the name of the person to embark
     */
    void embark(const std::string& name);

    /**
     * Disembark a person from the boat
     * @param name the name of the person to disembark
     */
    void disembark(const std::string& name);


    /**
     * Move the boat from one bank to the other
     */
    void moveBoat();

    /**
     * Manage a command entered by the user
     * @param s the command entered by the user and its parameters
     */
    void manageCommand(const std::string& s);

    /**
     * Check if the game is running
     * @return true if the game is running, false otherwise
     */
    bool isRunning();

    /**
     * Fill the left Bank with everyone
     */
    void fillLeftBank();
};

#endif //RIVER_CONTROLLER_HPP
