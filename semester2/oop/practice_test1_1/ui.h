#pragma once
#include "service.h"

class Ui {
private:
    Service &service;
    void print_menu();
    void add_station_ui();
    void display_stations();
    void sort_ui();
    public:
    Ui(Service &s);
    void start();
};
