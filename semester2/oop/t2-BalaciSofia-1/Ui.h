//
// Created by balac on 5/8/2025.
//

#ifndef UI_H
#define UI_H
#include "Service.h"

class Ui {
private:
    Service service;
public:
    Ui(Service service);
    void print_menu();
    void start();
    void ui_addCar();
    void ui_displayCars();
};


#endif //UI_H
