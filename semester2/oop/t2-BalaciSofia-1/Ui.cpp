//
// Created by balac on 5/8/2025.
//

#include "Ui.h"

#include <iostream>
Ui::Ui(Service service) {
    this->service = service;
}
void Ui::print_menu() {
    std::cout<<"1.\n";
    std::cout<<"2.\n";
    std::cout<<"3.\n";
    std::cout<<"4.Exit\n";
}

void Ui::ui_addCar() {
    std::string bodyStyle,engineType;
    int autonomy;
    std::cout<<"Enter body style: (Sedan/Convertible)";//sedan 800 conv 1000
    std::getline(std::cin, bodyStyle);
    std::cout<<"Enter engine type: (Electric/Turbo)";//base 3000
    std::getline(std::cin, engineType);
    if (engineType == "Electric") {
        std::cout<<"Enter autonomy: ";
        std::cin>>autonomy;
        double p=this->service.addCar(bodyStyle,engineType,autonomy);
        std::cout<<"total price of this car: "<<p<<"\n";
        std::cout<<"Car added successfully\n";
    }
    else if (engineType == "Turbo") {
        double p=this->service.addCar(bodyStyle,engineType,-1);
        std::cout<<"total price of this car: "<<p<<"\n";
        std::cout<<"Car added successfully\n";
    }
    else {
        std::cout<<"Invalid Engine";
    }
}

void Ui::ui_displayCars() {
    std::vector<Car> cars=this->service.getCars();
    for (auto car:cars) {
        std::cout<<car.getBodyStyle();
        std::cout<<car.getEngine()->toString()<<std::endl;
        std::cout<<"total price of this car: "<<car.computePrice();
    }
}
void Ui::start() {
    int option;
    while (true) {
        print_menu();
        std::cout<<" >>>";
        std::cin>>option;
        std::cin.clear();
        std::cin.ignore();
        switch (option) {
            case 1:
                ui_addCar();
                break;
            case 2:
                ui_displayCars();
                break;
            case 3:
                break;
            case 4:
                std::cout<<"Exit";
            return;
            default:
                std::cout<<"Invalid option";
            break;
        }
    }
}