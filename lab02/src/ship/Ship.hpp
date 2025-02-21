/**
 * @file Implementation of the Ship class.
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
 */
#pragma once

#include <ostream>
#include <cstdlib>

class Ship;

/**
 * @brief Implement the operator<< to format the Ship class to an output stream
 * @param os the output stream of interest
 * @param ship the ship to format
 * @return the changed output stream
 */
std::ostream &operator<<(std::ostream &os, const Ship &ship);

/**
 * @brief Abstract class representing a spaceship. It can have a nick name and
 * always has a factory number. It also has a specific weight and a specific speed.
 *
 */
class Ship {
private:
   std::optional<std::string> nickName;
   size_t factoryNumber;

public:

   /**
    * @brief Destructor of the Ship class. Virtual so that it can be overwritten
    * by the derived classes at the starting point of the destruction.
    */
   virtual ~Ship() = default;

   /**
    * @brief Format the ship to an output stream
    * @param os the output stream of interest
    * @return the changed output stream
    */
   virtual std::ostream &formatToStream(std::ostream &os) const;

   /**
    * @brief Get the weight of the ship. Pure virtual function.
    * @return the weight of the ship
    */
   virtual long double getWeight() const = 0;

   /**
    * @brief Get the speed of the ship. Pure virtual function.
    * @return the speed of the ship
    */
   virtual unsigned long long int getSpeed() const = 0;

   /**
    * @brief Get the factory name of the ship. Pure virtual function.
    * @return the factory name of the ship
    */
   virtual std::string getFactoryName() const = 0;

   /**
    * @brief Set the nick name of the ship
    */
   void setNickName(const std::string &nickName);

   /**
    * @brief Get the factory number of the ship
    * @return the factory number of the ship
    */
   size_t getFactoryNumber() const;

   /**
    * @brief Get the fuel consumption of the ship for the given
    * distance and the given speed
    * @param distance the distance to travel
    * @param speed the speed at which the ship will travel
    */
    long double fuelConsumption(long double distance, unsigned long long int speed) const;

   /**
    * @brief Constructor of the Ship class
    * @param _factoryNumber the factory number of the ship
    */
   explicit Ship(size_t _factoryNumber);

};
