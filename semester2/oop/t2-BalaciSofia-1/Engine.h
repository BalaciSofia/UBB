//
// Created by balac on 5/8/2025.
//

#ifndef ENGINE_H
#define ENGINE_H
#include <string>


class Engine {
protected:
    double basePrice;
public:
    Engine();
    virtual double getPrice()=0;
    virtual std::string toString()=0;
};



#endif //ENGINE_H
