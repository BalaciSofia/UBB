//
// Created by balac on 5/8/2025.
//

#ifndef TURBOENGINE_H
#define TURBOENGINE_H
#include "Engine.h"


class TurboEngine:public Engine {
public:
    TurboEngine()=default;
    double getPrice() override;
    std::string toString() override;
};



#endif //TURBOENGINE_H
