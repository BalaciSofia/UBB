//
// Created by balac on 5/8/2025.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "Building.h"


class Block : public Building {
private:
    int total_apartments;
    int ocupied_apartments;
public:
    Block(std::string address, int year, int total_apartments, int ocupied_apartments);
    bool mustBeRestored() override;
    bool mustBeDemolished() override;
    std::string toString() override;
};



#endif //BLOCK_H
