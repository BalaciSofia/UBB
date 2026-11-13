//
// Created by balac on 5/8/2025.
//

#ifndef BUILDING_H
#define BUILDING_H
#include <string>


class Building {
protected:
    std::string address;
    int year;
public:
    Building(std::string address, int year);
    virtual bool mustBeRestored() = 0;
    virtual bool mustBeDemolished() = 0;
    std::string getAddress();
    int getYear();
    virtual std::string toString() = 0;
};



#endif //BUILDING_H
