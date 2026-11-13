//
// Created by balac on 5/8/2025.
//

#ifndef ELECTRICENGINE_H
#define ELECTRICENGINE_H
#include <string>

#include "Engine.h"


class ElectricEngine:public Engine {
    private:
    int autonomy;
public:
    ElectricEngine(int autonomy);
    double getPrice();
    std::string toString();
};



#endif //ELECTRICENGINE_H
