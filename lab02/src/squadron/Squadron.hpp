/**
 * @file Implementation of the Squadron class.
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
 */
#pragma once

#include <string>
#include "src/ship/Ship.hpp"

class Squadron;

/**
 * @brief Implement the operator+ to add a ship to a squadron
 * @param rhs the right hand side of the operator which is a squadron
 * @param lhs the left hand side of the operator which is a ship
 * @return a new squadron with the ship added
 */
[[nodiscard]] Squadron operator+(const Squadron &rhs, Ship &lhs);

/**
 * @brief Implement the operator- to remove a ship from a squadron
 * @param rhs the right hand side of the operator which is a squadron
 * @param lhs the left hand side of the operator which is a shipnd
 * @return a new squadron with the ship removed
 */
[[nodiscard]] Squadron operator-(const Squadron &rhs, Ship &lhs);

/**
 * @brief Implement the operator<< to format the squadron to an output stream
 * @param os the output stream of interest
 * @param squadron the squadron to format
 * @return the output stream changed
 */
std::ostream &operator<<(std::ostream &os, const Squadron &squadron);

/**
 * @brief Squadron class is used to represent a squadron of ships. It is a linked list of ships.
 * Each squadron has a name, a potential chief and a list of ships that are a part of the
 * squadron. The rule of five has been followed to ensure that the class corresponds to
 * the extended canonical form.
 */
class Squadron {
public:
   using value_type = Ship;
   using pointer = Ship *;
   using reference = Ship &;
   using const_reference = const Ship &;

   /**
    * @brief Constructor of the Squadron class
    * @param _name the name of the squadron
    */
   explicit Squadron(const std::string &_name);

   // Rule of Five

   /**
    * Destructor of the Squadron class
    */
   ~Squadron();

   /**
    * @brief Copy constructor of the Squadron class
    * @param other the squadron to copy
    */
   Squadron(const Squadron &other);

   /**
    * @brief Move constructor of the Squadron class
    * @param other the squadron to move
    */
   Squadron(Squadron &&other) noexcept;

   /**
    * @brief Copy assignment operator of the Squadron class
    * @param other the squadron to copy
    * @return the instance of the squadron which has the elements
    * of the copied squadron
    */
   Squadron &operator=(const Squadron &other);

   /**
    * @brief Move assignment operator of the Squadron class
    * @param other the squadron to move
    * @return the instance of the squadron which has the elements
    * of the moved squadron
    */
   Squadron &operator=(Squadron &&other) noexcept;

   /**
    * @brief Add a ship to the squadron
    * @param ship ship to add to the squadron
    * @return the instance of the squadron with the ship added
    */
   Squadron &addShip(reference ship);

   /**
    * @brief Add a ship to a copied instance of the squadron
    * @param ship ship to add to the new squadron
    * @return the newly created instance of the squadron
    */
   [[nodiscard]] Squadron addShipCopy(reference ship) const;

   /**
    * @brief Delete a ship from the squadron
    * @param ship ship to delete
    * @return the instance of the squadron with the ship deleted
    */
   Squadron &deleteShip(reference ship);

   /**
    * @brief Delete a ship from a copied instance of the squadron
    * @param ship ship to delete from the new squadron
    * @return the newly created instance of the squadron
    */
   [[nodiscard]] Squadron deleteShipCopy(reference ship) const;

   /**
    * @brief Implement the operator+= on the squadron to add a ship
    * @param lhs the left hand side of the operator which is a ship
    * @return the instance of the squadron with the ship added
    */
   Squadron &operator+=(reference lhs);

   /**
    * @brief Implement the operator-= on the squadron to remove a ship
    * @param lhs the left hand side of the operator which is a ship
    * @return the instance of the squadron with the ship removed
    */
   Squadron &operator-=(reference lhs);

   /**
    * @brief Sets chief to the squadron. If the chief is not a part
    * of the squadron, it is added to the squadron.
    * @param newChief the ship to set as the chief
    */
   void setChief(reference newChief);

   /**
    * @brief Resets the chief of the squadron. Does not remove the ship from the squadron.
    */
   void removeChief();

   /**
    * @brief Get the i-th ship of the squadron
    * @throw std::out_of_range if i is out of the index
    * @param i index of the ship of interest
    * @return a reference on the ship of interest
    */
   [[nodiscard]] reference get(size_t i) const;

   /**
    * @brief Change the name of the squadron
    * @param newName the new name of the squadron
    */
   void setName(const std::string &newName);

   /**
    * @brief Checks if the squadron is empty
    * @return true if it is, false if it is not
    */
   bool empty() const;

   /**
    * @brief Method to determine the fuel consumption of the squadron
    * @throw std::run_time_error if Squadron is empty
    * @throw std::invalid_argument if distance or speed is negative or if speed is greater than the maximum speed
    * @param distance the distance the squadron will travel
    * @param speed the speed at which the squadron will travel
    * @return the estimate consumption for the whole squadron
    */
   long double fuelConsumption(long double distance, unsigned long long int speed) const;

   /**
    * @brief Get the maximum speed at which the squadron can travel
    * @return the maximum speed at which the squadron can travel
    */
   unsigned long long int getMaximumSpeed() const;

   /**
    * @brief Get the total weight of the squadron
    * @return the total weight of the squadron
    */
   long double getWeight() const;

   /**
    * @brief Format the squadron for an output stream
    * @param os the output stream of interest
    * @return the changed output stream
    */
   std::ostream &formatToStream(std::ostream &os) const;

private:

   struct Node {
      pointer value;
      Node *next;
   };

   Node *head{};
   std::string name;
   pointer chief{};
   size_t size{};



   void initSquadron(const std::string &n, pointer _chief = nullptr);

   /**
    * @brief Helper methode to delete the squadron
    */
   void deleteSquadron();

   /**
    * @brief Helper method to copy a squadron
    * @param other the squadron to copy
    */
   void copySquadron(const Squadron &other);

   /**
    * @brief Helper method to exchange every attribute from
    * one squadron to another
    * @param other the squadron to exchange from
    */
   void exchange(Squadron &other);

   /**
    * @brief Helper method to check if the squadron contains a ship
    * @param ship the ship of interest
    * @return true if it is in the squadron, false if it is not
    */
   bool contains(reference ship);

};


