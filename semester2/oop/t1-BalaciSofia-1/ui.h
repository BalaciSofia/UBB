#pragma once
#include "service.h"

class Ui {
private:
    Service &service;
    void print_menu();
    void ui_addSchool();
    void ui_display();
    void ui_sort();
    public:
    Ui(Service &s): service(s) {};
    void start();
};
