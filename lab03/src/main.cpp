/**
 * @file main.cpp
 * @brief Entry point for the application that handles the creation of a Controller
 * and runs it until it is finished,
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 * @since 2024-05-21
 */
#include <iostream>
#include <map>
#include "Controller.hpp"
#include "person/IndependentPerson.hpp"
#include "person/Boy.hpp"
#include <functional>

int main() {

   Controller controller;

   while (controller.isRunning()) {
      controller.nextTurn();
   }

   return EXIT_SUCCESS;
}