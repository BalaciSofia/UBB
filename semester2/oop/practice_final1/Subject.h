//
// Created by balac on 6/15/2025.
//

#ifndef SUBJECT_H
#define SUBJECT_H


#include <vector>
#include "Observer.h"
#include <memory>

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void addObserver(std::shared_ptr<Observer> observer){
        this->observers.push_back(observer);
    }
    void notifyObservers(){
        for (auto i : this->observers)
            i->update();
    }
};



#endif //SUBJECT_H
