#ifndef RIVER_GIRL_HPP
#define RIVER_GIRL_HPP


#include "Kid.hpp"

/**
 * @file Girl.hpp
 * @brief Definition of the Girl class
 * @author REDACTED
 * @author REDACTED
 * @author Quentin Surdez
 */
class Girl : public Kid {
public:
    /**
     * Constructor
     * @param name the name of the girl
     * @param father the father of the girl
     * @param mother the mother of the girl
     */
    Girl(const std::string& name, Person* father, Person* mother);

    /**
     * Tell if a girl can be with the other people in a container
     * @param container the container to check
     * @return a StateResult object containing the result of the check
     */
    StateResult isStateValid(const Container& container) override;

private:
    static const std::string& girlWithFather;
};


#endif //RIVER_GIRL_HPP
