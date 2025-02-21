/**
 * @file Implementation of the Vec2D struct
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */


#include "Vec2D.hpp"
#include "Random.hpp"
#include <cmath>

Vec2D::Vec2D(int x_, int y_) : x(x_), y(y_) {}

Vec2D::Vec2D() : x(0), y(0) {}

size_t Vec2D::calculateDistance(const Vec2D& other) const {
   /*Vec2D difference = subtraction(other).absValue();
   size_t casesNotInDiagonal = std::abs(difference.x-difference.y);
   return std::min(difference.x, difference.y) + casesNotInDiagonal;*/
   double x_ = std::abs(x - other.x);
   double y_ = std::abs(y - other.y);
   return (size_t) std::round(std::hypot(x_, y_));
}


Vec2D Vec2D::subtraction(const Vec2D& other) const {
   return {this->x - other.x, this->y - other.y};
}

Vec2D Vec2D::addition(const Vec2D& other) const {
   return {this->x + other.x, this->y + other.y};
}

Vec2D Vec2D::getDirection(const Vec2D& other) const {
   int x_ = other.x - x;
   int y_ = other.y - y;

   return {
           x_ == 0 ? 0 : x_ / std::abs(x_),
           y_ == 0 ? 0 : y_ / std::abs(y_)
   };
}

Vec2D Vec2D::getRandomVector(size_t maxX, size_t maxY) {
   return {
      Random::generateFrom0(maxX - 1),
      Random::generateFrom0(maxY - 1)
   };
}
