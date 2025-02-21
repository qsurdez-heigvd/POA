/**
 * @file Controller.cpp
 * @brief Implementation of the Controller class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */

#include <iostream>
#include "Controller.hpp"
#include "person/Person.hpp"
#include "person/Boy.hpp"
#include "person/Girl.hpp"
#include "person/Thief.hpp"
#include <regex>

const std::map<std::string, Controller::CommandDescription> Controller::COMMANDS = {{"p", {"p : afficher", [](
    Controller& c, const std::string&) { c.display(); }}},
                                                                                    {"e", {"e <nom> : embarquer <nom>", [](
                                                                                        Controller& c,
                                                                                        const std::string& name) {
                                                                                        c.embark(name);
                                                                                    }}},
                                                                                    {"d", {"d <nom> : debarquer <nom>", [](
                                                                                        Controller& c,
                                                                                        const std::string& name) {
                                                                                        c.disembark(name);
                                                                                    }}},
                                                                                    {"m", {"m : deplacer bateau", [](
                                                                                        Controller& c,
                                                                                        const std::string&) { c.moveBoat(); }}},
                                                                                    {"r", {"r : reinitialiser", [](
                                                                                        Controller& c,
                                                                                        const std::string&) { c.reset(); }}},
                                                                                    {"q", {"q : quitter", [](
                                                                                        Controller& c,
                                                                                        const std::string&) { c.quit(); }}},
                                                                                    {"h", {"h : menu", [](Controller& c,
                                                                                                          const std::string&) { c.showMenu(); }}}};

const std::string Controller::BANK = "----------------------------------------------------------";

const std::string Controller::RIVER = "==========================================================";


Controller::Controller() : leftBank(new Bank{"Gauche"}), rightBank(new Bank("Droite")), turn(0),
                           boat(new Boat("Bateau", leftBank)), lastState{true} {
    Person* father = new IndependentPerson("pere");
    persons.push_back(father);
    Person* mother = new IndependentPerson("mere");
    persons.push_back(mother);
    persons.push_back(new Boy("paul", father, mother));
    persons.push_back(new Boy("pierre", father, mother));
    persons.push_back(new Girl("julie", father, mother));
    persons.push_back(new Girl("jeanne", father, mother));
    Person* policier = new IndependentPerson("policier");
    persons.push_back(policier);
    persons.push_back(new Thief("voleur", policier));
    fillLeftBank();
    running = true;
}

void Controller::movePerson(std::string name, Container& from, Container& to) {

    /*Container copyFrom(from);

    copyFrom.removePerson(person);

    StateResult result = copyFrom.isContainerValid();
    if(!result.isValid()) {
        std::cout << result.getError() << std::endl;
        return;
    }
    Container copyTo(to);
    copyTo.addPerson(person);
    result = copyTo.isContainerValid();
    if(!result.isValid()) {
        std::cout << result.getError() << std::endl;
        return;
    }
    from.removePerson(person);
    to.addPerson(person);
    */
    Person* person = from.findByName(name);
    if (person == nullptr) {
        lastState = {false, "Personne pas présente"};
        return;
    }
    Container* copyFrom = from.clone();
    Container* copyTo = to.clone();
    copyFrom->removePerson(person);
    StateResult result = copyFrom->isContainerValid();


    if (result.isValid()) {
        copyTo->addPerson(person);
        result = copyTo->isContainerValid();
        if (result.isValid()) {
            from.removePerson(person);
            to.addPerson(person);
            lastState = {true };
        }
    }
    delete copyFrom;
    delete copyTo;
    lastState = result;
    //std::cout << result.getError() << std::endl;

    /*from.removePerson(person);
    to.addPerson(person);
    StateResult result = from.isContainerValid();
    if(result.isValid()) {
        result = to.isContainerValid();
        if(result.isValid()) {
            return;
        }
    }
    from.addPerson(person);
    to.removePerson(person);
    std::cout << result.getError() << std::endl;*/
}

void Controller::display() const {
    std::cout << BANK + "\n";
    leftBank->display();
    std::cout << BANK + "\n";
    if (boat->getBank() == leftBank) {
        boat->display();
    }
    std::cout << RIVER + "\n";
    if (boat->getBank() == rightBank) {
        boat->display();
    }
    std::cout << BANK + "\n";
    rightBank->display();
    std::cout << BANK + "\n";
}

void Controller::displayInitialSituation() const {
    std::cout << "1. Situation initiale:" << std::endl;
    showMenu();
    display();
}



Controller::~Controller() {
    delete leftBank;
    delete rightBank;
    delete boat;
    for (auto p: persons) {
        delete p;
    }
}

void Controller::embark(const std::string& name) {
    movePerson(name, *boat->getBank(), *boat);
}

void Controller::disembark(const std::string& name) {
    movePerson(name, *boat, *boat->getBank());
}

void Controller::moveBoat() {
    lastState = boat->canMove();
    if(lastState.isValid()) {
        boat->setBank(boat->getBank() == leftBank ? rightBank : leftBank);
    }
}

void Controller::showMenu() const {
    for (const auto& [key, cmd]: COMMANDS) {
        std::cout << cmd.description << '\n';
    }
}

void Controller::manageCommand(const std::string& s) {
    std::string command, param;


    std::size_t spacePos = s.find(' ');
    if (spacePos != std::string::npos) {
        command = s.substr(0, spacePos);
        param = s.substr(spacePos + 1);
    } else {
        command = s;
        param = "";
    }
    if(!COMMANDS.contains(command)) {
        lastState = {false, "Commande invalide"};
    } else {
        lastState = {true};
        COMMANDS.at(command).function(*this, param);
    }

}


void Controller::nextTurn() {

    if (turn == 0) {
        displayInitialSituation();
    }
    std::cout << turn++ << '>';
    std::string command;
    std::getline(std::cin, command);
    command.erase(0, command.find_first_not_of(" \t\n\r\f\v"));

    manageCommand(command);
    if(lastState.isValid()) {
        display();
    } else {
        std::cout << "###" + lastState.getError() << std::endl;
    }

    if (rightBank->size() == this->persons.size()) {
        std::cout << "Vous avez gagne ! Bravo !" << std::endl;
        running = false;
    }
}

void Controller::quit() {
    running = false;
}

bool Controller::isRunning() {
    return running;
}

void Controller::reset() {
    boat->setBank(leftBank);
    boat->clear();
    rightBank->clear();
    leftBank->clear();

    fillLeftBank();
    lastState = {true};
    turn = 0;
}

void Controller::fillLeftBank() {
    for(auto p : persons) {
        leftBank->addPerson(p);
    }
}
