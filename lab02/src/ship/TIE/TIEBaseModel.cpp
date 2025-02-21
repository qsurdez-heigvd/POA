
#include "TIEBaseModel.hpp"

TIEBaseModel::TIEBaseModel(size_t _factoryNumber) : Ship(_factoryNumber) {}

std::string TIEBaseModel::getFactoryName() const {
    return "TIE/";
}

