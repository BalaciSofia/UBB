//
// Created by balac on 5/8/2025.
//

#ifndef HOUSE_H
#define HOUSE_H
#include "Building.h"


class House:public Building {
private:
    std::string type;
    bool isHistorical;
public:
    House(std::string address,int year,std::string type, bool isHistorical);
    bool mustBeRestored() override;
    bool mustBeDemolished() override;
    std::string toString()override;
};



#endif //HOUSE_H
