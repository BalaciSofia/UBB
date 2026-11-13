//
// Created by balac on 5/8/2025.
//

#include "Car.h"

Car::Car(std::string bodyStyle,Engine* engine) :bodyStyle(bodyStyle),engine(engine){}

double Car::computePrice() {
    double price;
    if (bodyStyle=="Sedan") {
        price=8000+this->engine->getPrice();
    }
    else if (bodyStyle=="Convertible") {
        price=this->engine->getPrice()+9000;
    }
    return price;
}

Engine* Car::getEngine() {
    return engine;
}

std::string Car::getBodyStyle() {
    return bodyStyle;
}