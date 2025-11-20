//
// Created by balac on 6/16/2025.
//
#include <iostream>
#include "Subject.h"
void Subject::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Subject::notifyObservers() {
    std::cout << "in update\n";
    for(auto i : observers)
        i->update();
}