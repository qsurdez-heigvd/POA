#ifndef RIVER_BANK_HPP
#define RIVER_BANK_HPP


#include "Container.hpp"

class Bank : public Container {

public:

    /**
     * Constructor
     * @param name the name of the bank
     */
    explicit Bank(const std::string& name);

    /**
     * Clone the bank
     * @return the cloned bank
     */
    Container* clone() override;
};


#endif //RIVER_BANK_HPP
