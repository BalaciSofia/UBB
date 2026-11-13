//
// Created by balac on 5/8/2025.
//

#include "Ui.h"

#include <iostream>
#include <limits>
#include <cctype> // for std::toupper

Ui::Ui(Controller &c): c(&c) {}

void Ui::print_menu() {
    std::cout << "============================\n";
    std::cout << "1: Add building\n";
    std::cout << "2: Show all buildings\n";
    std::cout << "3: Sort buildings\n";
    std::cout << "4: Write to file\n";
    std::cout << "5: Exit\n";
}

void Ui::ui_add_building() {
    std::string address;
    int year;
    char w;
    std::cout << "Enter H to add a house or B to add a block: ";
    std::cin >> w;
    w = std::toupper(w); // Make input case-insensitive
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (w == 'H') {
        std::cout << "Enter address: ";
        std::getline(std::cin, address);
        std::cout << "Enter year: ";
        std::cin >> year;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string type;
        std::cout << "Enter type: ";
        std::getline(std::cin, type);
        std::string historicalInput;
        bool isHistorical = false;
        std::cout << "Is it historical? (yes/no): ";
        std::getline(std::cin, historicalInput);
        if (historicalInput == "yes" || historicalInput == "Yes")
            isHistorical = true;

        try {
            this->c->add_Building_house(address, year, type, isHistorical);
            std::cout << "House added successfully!\n";
        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    } else if (w == 'B') {
        std::cout << "Enter address: ";
        std::getline(std::cin, address);
        std::cout << "Enter year: ";
        std::cin >> year;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int total_apartments;
        std::cout << "Enter total apartments: ";
        std::cin >> total_apartments;
        int occupied_apartments;
        std::cout << "Enter occupied apartments: ";
        std::cin >> occupied_apartments;

        try {
            this->c->add_Building_block(address, year, total_apartments, occupied_apartments);
            std::cout << "Block added successfully!\n";
        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Invalid option.\n";
    }
}

void Ui::display_buildings() {
    std::vector<Building*> buildings = c->get_all_buildings();
    for (auto building : buildings) {
        std::cout << building->toString() << std::endl;
        if (building->mustBeRestored()) {
            std::cout << "This building must be restored.\n";
        }
        if (building->mustBeDemolished()) {
            std::cout << "This building must be demolished.\n";
        }
    }
}

void Ui::display_building_sorted() {

    std::vector<Building*> buildings = c->get_all_buildings_sorted();
    for (auto building : buildings) {
        std::cout << building->toString() << std::endl;
        if (building->mustBeRestored()) {
            std::cout << "This building must be restored.\n";
        }
        if (building->mustBeDemolished()) {
            std::cout << "This building must be demolished.\n";
        }
    }
}

void Ui::write_toFile() {
    std::string f1, f2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any leftover input
    std::cout << "Enter the name of the file for buildings to be restored: ";
    std::getline(std::cin, f1);
    std::cout << "Enter the name of the file for buildings to be demolished: ";
    std::getline(std::cin, f2);
    try {
        this->c->writeToFile(f1, f2);
        std::cout << "Buildings written to file successfully!\n";
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Ui::start() {
    this->c->add_Building_house("strada mea", 2000, "roz", false);
    this->c->add_Building_block("strada ta", 1950, 10, 5);
    while (true) {
        int option;
        this->print_menu();
        std::cout << std::endl << "Choose an option: ";
        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (option) {
            case 1:
                this->ui_add_building();
                break;
            case 2:
                this->display_buildings();
                break;
            case 3:
                this->display_building_sorted();
                break;
            case 4:
                this->write_toFile();
                break;
            case 5:
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    }
}
