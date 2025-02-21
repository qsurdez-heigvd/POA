/**
 * @file Implementation of the FieldController class
 *
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include <iostream>
#include <functional>
#include "FieldController.hpp"

const std::string FieldController::CORNER = "+";
const std::string FieldController::HORIZONTAL_BORDER = "-";
const std::string FieldController::VERTICAL_BORDER = "|";

struct FieldController::Command {
    std::string description;
    std::function<void(FieldController&)> action;
};

const std::map<std::string, FieldController::Command> FieldController::COMMANDS = {
        {"q", {"quit",
                      [](FieldController& f) { f.stop(); }}},
        {"n", {"next",
                      [](FieldController& f) { f.nextTurn(); }}},
        {"s", {"statistics",
                      [](FieldController&  f) {
                          std::cout << FieldStatsCalculator::simulate(
                                  f.currentField.getHeight(), f.currentField.getWidth(),
                                  f.initialNbVampire, f.initialNbHuman) << std::endl;
        }}},
};

FieldController::FieldController(Field& field)
        : currentField(field),
          initialNbHuman(field.getNbHuman()),
          initialNbVampire(field.getNbVampire()) {}

void FieldController::printHorizontalBorder(const Field& field, std::string& output) {
   output += CORNER;
   for (size_t j = 0; j < field.getWidth(); j++) {
      output += HORIZONTAL_BORDER;
   }
   output += CORNER + "\n";
}

void FieldController::printVerticalBorder(const Field& field, std::string& output) {
   auto map = field.fieldToStringVector();
   for (const auto& line: map) {
      output += VERTICAL_BORDER;
      for (const auto& humanoid: line) {
         if (humanoid.empty()) {
            output += ' ';
         } else {
            output += humanoid;
         }
      }
      output += VERTICAL_BORDER + "\n";
   }
}

std::string FieldController::displayFieldToString(const Field& field) {
   std::string output;
   printHorizontalBorder(field, output);
   printVerticalBorder(field, output);
   printHorizontalBorder(field, output);
   return output;
}

void FieldController::display(const Field& field) {
   std::cout << displayFieldToString(field);
   std::cout << std::flush;
}

void FieldController::start() {
   running = true;
   display(currentField);
   while (running && currentField.isFinished() == Status::RUNNING) {
      std::cout << "[" + std::to_string(currentField.getTurn()) + "] ";
      for (const auto& [key, cmd]: COMMANDS) {
         std::cout << key << "<" << cmd.description << " ";
      }
      std::cout << ": ";
      std::string command;
      std::getline(std::cin, command);

      auto it = COMMANDS.find(command);
      if (it == COMMANDS.end()) {
         std::cout << "Invalid command << " << command << std::endl;
         continue;
      }
      handleCommand(it->second);
   }
   running = false;
}

void FieldController::handleCommand(const Command& command) {
   command.action(*this);
}

void FieldController::stop() {
   running = false;
}

void FieldController::nextTurn() {
   currentField.nextTurn();
   display(currentField);
}







