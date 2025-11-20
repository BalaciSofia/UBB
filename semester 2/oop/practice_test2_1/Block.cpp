//
// Created by balac on 5/8/2025.
//

#include "Block.h"
Block::Block(std::string address, int year, int total_apartments, int ocupied_apartments):
        Building(address, year), total_apartments{total_apartments}, ocupied_apartments{ocupied_apartments} {}

bool Block::mustBeRestored() {
        if (this->getYear()<2025-40) {
                double percentage = (double)this->ocupied_apartments/(double)this->total_apartments;
                if (percentage>0.8) {
                        return true;
                }
        }
        return false;
}

bool Block::mustBeDemolished() {
        double percentage = (double)this->ocupied_apartments/(double)this->total_apartments;
        if (percentage<0.05) {
                return true;
        }
        return false;
}

std::string Block::toString() {
        return "Address: " + this->address + " | Year: " + std::to_string(this->year) +
               " | Total apartments: " + std::to_string(this->total_apartments) +
               " | Occupied apartments: " + std::to_string(this->ocupied_apartments);;
}