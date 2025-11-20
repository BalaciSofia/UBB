//
// Created by balac on 5/8/2025.
//

#include "House.h"

House::House(std::string address, int year, std::string type, bool isHistorical): Building(address, year), type{type}, isHistorical{isHistorical} {}

bool House::mustBeRestored() {
    if (this->getYear()<2025-100) {
        return true;
    }
    return false;
}

bool House::mustBeDemolished() {
    if (this->isHistorical) {
        return false;
    }
    return true;
}

std::string House::toString() {
    return "Address: " + this->address + " | Year: " + std::to_string(this->year) +
           " | Type: " + this->type + " | Is historical: " + (this->isHistorical ? "Yes" : "No");
}