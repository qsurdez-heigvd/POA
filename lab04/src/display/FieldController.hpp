/**
 * @file Declaration of the FieldController class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <string>
#include "../field/Field.hpp"
#include "../stats/FieldStatsCalculator.hpp"

#include <map>

/**
 * FieldController a class used to display the field and run it. It will
 * have a field and will display it on the console. It will be able to handle
 * different commands passed by the terminal. n for the next turn, q for quitting
 * and s to have the stats of many simulations.
 */
class FieldController {
public:
    explicit FieldController(Field& field);

    /**
     * Method to convert the currentField to a string
     * @param field the currentField to convert
     * @return the string representing the currentField
     */
    static std::string displayFieldToString(const Field& field);

    /**
     * Method to simulate the currentField and display it
     * @param field the currentField to simulate
     */
     void start();

     /**
      * Method to stop the simulation
      */
     void stop();

     /**
      * Method to go to the next turn of the simulation
      */
     void nextTurn();

    /**
     * Default constructor of the class
     */
    FieldController() = delete;

private:
    struct Command;
    static const std::map<std::string, Command> COMMANDS;
    static const std::string CORNER;
    static const std::string HORIZONTAL_BORDER;
    static const std::string VERTICAL_BORDER;
    Field& currentField;
    bool running = false;
    size_t initialNbHuman;
    size_t initialNbVampire;

    /**
     * Method to handle the command given by the user
     * @param command the command to handle
     */
     void handleCommand(const Command& command);

    /**
     * Method to print the horizontal border of the currentField
     * @param field the currentField to print the border of
     * @param output the string to print the border to
     */
    static void printHorizontalBorder(const Field& field, std::string& output);

    /**
     * Method to print the vertical border of the currentField
     * @param field the currentField to print the border of
     * @param output the string to print the border to
     */
    static void printVerticalBorder(const Field& field, std::string& output);

    /**
     * Method to display the currentField on the console
     * @param field the currentField to display
     */
    static void display(const Field& field);

};

