#ifndef RIVER_BOY_HPP
#define RIVER_BOY_HPP


#include "Kid.hpp"

/**
 * @file Boy.hpp
 * @brief Definition of the Boy class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class Boy : public Kid {
public:
    /**
     * Constructor
     * @param name the name of the boy
     * @param father the father of the boy
     * @param mother the mother of the boy
     */
    Boy(const std::string& name, Person* father, Person* mother);

    /**
     * Tell if a boy can be with the other people in a container
     * @param container the container to check
     * @return a StateResult object containing the result of the check
     */
    StateResult isStateValid(const Container &container) override;
private:
    static const std::string &boyWithMother;
};


#endif //RIVER_BOY_HPP
