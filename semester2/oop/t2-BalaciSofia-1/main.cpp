#include <iostream>

#include "Service.h"
#include "Ui.h"
//
// Created by balac on 5/8/2025.
//
int main() {
    Service service;
    Ui ui(service);
    ui.start();
    return 0;
}
