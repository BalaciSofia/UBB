//
// Created by balac on 5/8/2025.
//

#include "Building.h"

Building::Building(std::string address, int year): address{address}, year{year} {}

std::string Building::getAddress() {
    return this->address;
}

int Building::getYear() {
    return this->year;
}


