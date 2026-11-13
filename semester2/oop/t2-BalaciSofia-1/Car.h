//
// Created by balac on 5/8/2025.
//

#ifndef CAR_H
#define CAR_H
#include <string>

#include "Engine.h"


class Car {
private:
    std::string bodyStyle;
    Engine* engine;
    public:
    Car(std::string bodyStyle,Engine* engine);
    double computePrice();
    Engine* getEngine();
    std::string getBodyStyle();
};



#endif //CAR_H
