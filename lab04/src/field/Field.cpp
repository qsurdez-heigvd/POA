/**
 * @file Implementation of the Field class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include <iostream>
#include "Field.hpp"
#include "../humanoids/Vampire.hpp"
#include "../humanoids/Human.hpp"
#include "../humanoids/Buffy.hpp"
#include "../utils/Random.hpp"

Field::Field(size_t height, size_t width, size_t nbVampire, size_t nbHuman) : height_(height), width_(width),
                                                                              nbVampire_(nbVampire), nbHuman_(nbHuman) {

   humanoids.emplace_back(std::make_shared<Buffy>(Vec2D::getRandomVector(width_ - 1, height_ - 1)));

   for (size_t i = 0; i < nbVampire; i++) {
      humanoids.emplace_back(std::make_shared<Vampire>(Vec2D::getRandomVector(width_ - 1, height_ - 1)));

   }
   for (size_t i = 0; i < nbHuman; i++) {
      humanoids.emplace_back(std::make_shared<Human>(Vec2D::getRandomVector(width_ - 1, height_ - 1)));

   }
   turn_ = 0;
}

size_t Field::getTurn() const {
   return turn_;
}

size_t Field::nextTurn() {
   // Déterminer les prochaines actions
   for (auto& humanoid: humanoids)
      humanoid->setAction(*this);
   // Executer les actions
   for (auto& humanoid: humanoids)
      humanoid->executeAction(*this);
   // Enlever les humanoides tués
   for (auto it = humanoids.begin(); it != humanoids.end();) {
      if (!(*it)->isAlive()) {
         it = humanoids.erase(it); // suppression de l’élément dans la liste
      } else
         ++it;
   }

   //std::cout << "Turn " << turn_ << " : " << nbVampire_ << " vampires, " << nbHuman_ << " humans" << std::endl;

   for (auto& it : humanoids) {
      if (it->getPosition().x < 0 || it->getPosition().x >= width_ || it->getPosition().y < 0 || it->getPosition().y >= height_) {
         std::cout << "Humanoid: " << it->getType() << " is out of bounds, pos: {" << it->getPosition().x << ", " <<
         it->getPosition().y << "}" << std::endl;
      }
   }

   return turn_++;
}

std::vector<std::vector<std::string>> Field::fieldToStringVector() const {
   std::vector<std::vector<std::string>> map(height_, std::vector<std::string>(width_, ""));
   for (const auto& humanoid: humanoids) {
      auto position = humanoid->getPosition();
      map[position.x][position.y] = humanoid->getType();
   }
   return map;
}

size_t Field::getHeight() const {
   return height_;
}

size_t Field::getWidth() const {
   return width_;
}

void Field::vampireKilled() {
   if (nbVampire_ > 0)
      nbVampire_--;
}

void Field::humanKilled() {
   if (nbHuman_ > 0)
      nbHuman_--;
}

void Field::vampireBorn() {
   nbVampire_++;
}

bool Field::aliveVampires() const {
   return nbVampire_ > 0;
}

bool Field::aliveHumans() const {
   return nbHuman_ > 0;
}

Status Field::isFinished() const {
   if (nbHuman_) {
      return nbVampire_ > 0 ? Status::RUNNING : Status::WIN;
   }
   return Status::LOSE;
}

void Field::addHumanoid(const std::shared_ptr<Humanoid>& humanoid) {
   humanoids.emplace_back(humanoid);
}
