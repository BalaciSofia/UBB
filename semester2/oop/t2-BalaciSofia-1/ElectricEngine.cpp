//
// Created by balac on 5/8/2025.
//

#include "ElectricEngine.h"

ElectricEngine::ElectricEngine(int autonomy): autonomy(autonomy) {
}

double ElectricEngine::getPrice() {
    return basePrice+autonomy*0.01;
}

std::string ElectricEngine::toString() {
    return "ElectricEngine with autonomy: " + std::to_string(autonomy) + " and price "+std::to_string(getPrice())+"\n";
}