//
// Created by David Berbecar on 01.05.2025.
//

#ifndef UI_H
#define UI_H
#include "Service.h"


class UI {
private:
    Service& service;
    void displayMenu();
    void addAnalysis();
    void displayAllAnalyses();
    void displayAnalysesByMonth();
    void isIll();
    void displayAnalysesBetweenDates();
    void writeToFile();
public:
    UI(Service& service);
    ~UI();
    void run();
};



#endif //UI_H
