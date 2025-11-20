//
// Created by balac on 6/16/2025.
//

#ifndef SUBJECT_H
#define SUBJECT_H


#include <vector>
#include <memory>
#include "observer.h"
class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void addObserver(std::shared_ptr<Observer> observer);
    void notifyObservers();
};


#endif //SUBJECT_H
