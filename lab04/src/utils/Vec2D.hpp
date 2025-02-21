/**
 * @file Declaration of the Vec2D struct
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#pragma once

#include <array>
#include <cstddef>

/**
 * Structure representing a 2D vector with integer coordinates
 */
struct Vec2D {
public:
    int x, y;

    /**
     * Constructor of the Vec2D struct
     * @param x_ x-coordinate of the vector
     * @param y_ y-coordinate of the vector
     */
    Vec2D(int x_, int y_);

    /**
     * Empty constructor of the struct
     */
    Vec2D();

    /**
     * Method to calculate the distance between two vectors
     * @param other the vector with which to calculate the distance
     * @return the distance between the two vectors
     */
    size_t calculateDistance(const Vec2D& other) const;

    /**
     * Method to calculate the subtraction of two vectors
     * @param other the vector with which to calculate the subtraction
     * @return a new vector representing the subtraction of the two vectors
     */
    Vec2D subtraction(const Vec2D& other) const;

   /**
    * Method to calculate the addition of two vectors
    * @param other the vector with which to calculate the addition
    * @return a new vector representing the addition of the two vectors
    */
    Vec2D addition(const Vec2D& other) const;

    /**
     * Method to calculate the direction from one vector to another
     * @param other the vector with which to calculate the direction
     * @return a new vector representing the direction in which the other vector is
     */
    Vec2D getDirection(const Vec2D& other) const;

    /**
     * Method to get a random vector from 0 to given bounds
     * @param maxX the max x-coordinate value
     * @param maxY
     * @return
     */
    static Vec2D getRandomVector(size_t maxX, size_t maxY);

};



