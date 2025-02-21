/**
 * @file Declaration of the Field class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <list>
#include <memory>
#include <vector>
#include "../humanoids/Humanoid.hpp"
#include "../utils/Status.hpp"

/**
 * Field class to represent the game. It will have a list of all humanoids. It will also have a height and a width
 * to represent the limits of the game. It will have the number of vampire and humans as to not iterate over the lists
 * to know how many vampires and humans are left within the list.
 */
class Field {
private:
    std::list<std::shared_ptr<Humanoid>> humanoids;
    size_t height_;
    size_t width_;
    size_t nbVampire_;
    size_t nbHuman_;
    size_t turn_;
public:

    /**
     * Constructor of the class
     * @param height height of the game
     * @param width width of the game
     * @param nbVampire nbVampire at the beginning of the game
     * @param nbHuman nbHuman at the beginning of the game
     */
    Field(size_t height, size_t width, size_t nbVampire, size_t nbHuman);

    /**
     * Getter for the turn_ attribute
     * @return the turn number of the simulation
     */
    size_t getTurn() const;

    /**
     * Method to go to the next turn
     * @return the number of the turn
     */
    size_t nextTurn();

    /**
     * Generic method to search for the closest Humanoid (either Vampire or Human)
     * @tparam T the type of humanoid we want to look for
     * @param hunter the humanoid looking for another humanoid
     * @return a shared pointer on the target
     */
    template<typename T>
    std::shared_ptr<T> findClosestHumanoid(const std::shared_ptr<Humanoid>& hunter) const;

    /**
     * Method to convert the field into a vector of strings
     * @return the vector of strings representing the field
     */
    [[nodiscard]] std::vector<std::vector<std::string>> fieldToStringVector() const;

    /**
     * Getter for the height_ attribute
     * @return the height_ attribute
     */
    size_t getHeight() const;

    /**
     * Getter for the width_ attribute
     * @return the width_ attribute
     */
    size_t getWidth() const;

    /**
     * Method to decrement the number of vampire
     */
    void vampireKilled();

    /**
     * Method to decrement the number of human
     */
    void humanKilled();

    /**
     * Method to increment the number of vampire
     */
    void vampireBorn();

    /**
     * Method to give the information if there are alive vampires in the currentField
     */
    bool aliveVampires() const;

    /**
     * Method to give the information if there are alive humans in the currentField
     */
    bool aliveHumans() const;

    /**
     * Method to know if the game is finished or not
     * @return true if finished false if running
     */
    Status isFinished() const;

   /**
    * Getter for the number of humans
    * @return the number of humans
    */
    size_t getNbHuman() const {
       return nbHuman_;
    };

    /**
     * Getter for the number of vampires
     * @return the number of vampires
     */
    size_t getNbVampire() const {
       return nbVampire_;
    };

    /**
     * Method to add a humanoid to the list within the field
     * @param humanoid the humanoid to add to the list
     */
    void addHumanoid(const std::shared_ptr<Humanoid>& humanoid);

};

#include "Field_Generic_Impl.hpp"

