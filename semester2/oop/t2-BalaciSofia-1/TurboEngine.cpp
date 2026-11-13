//
// Created by balac on 5/8/2025.
//

#include "TurboEngine.h"


double TurboEngine::getPrice() {
    return basePrice+100;
}

std::string TurboEngine::toString() {
    return "TurboEngine with price" + std::to_string(getPrice()) + "\n";
}