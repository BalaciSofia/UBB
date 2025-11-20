//
// Created by balac on 5/8/2025.
//

#ifndef UI_H
#define UI_H
#include "controller.h"


class Ui {
private:
    Controller *c;
public:
    Ui(Controller &c);
    void print_menu();
    void start();
    void ui_add_building();
    void display_buildings();
    void display_building_sorted();
    void write_toFile();
};



#endif //UI_H
