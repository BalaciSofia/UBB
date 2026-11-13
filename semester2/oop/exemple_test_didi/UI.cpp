//
// Created by David Berbecar on 01.05.2025.
//

#include "UI.h"

#include <iostream>

#include "BMI.h"
#include "BP.h"

UI::UI(Service &service): service{service}
{

}

UI::~UI() {

}

void UI::displayMenu() {
    std::cout<<"1. Add analysis"<<std::endl;
    std::cout<<"2. Display all analyses"<<std::endl;
    std::cout<<"3. Display analyses by month"<<std::endl;
    std::cout<<"4. Check if the person is ill"<<std::endl;
    std::cout<<"5. Display analyses between dates"<<std::endl;
    std::cout<<"6. Write to file"<<std::endl;
    std::cout<<"0. Exit"<<std::endl;
}

void UI::addAnalysis() {
    std::string type, date;
    double value1, value2;

    std::cout<<"Enter type(BMI or BP): ";
    std::getline(std::cin, type);
    if (type != "BMI" and type != "BP") {
        std::cout<<"Invalid type!"<<std::endl;
        return;
    }
    std::cout<<"Enter date (YYYY.MM.DD): ";
    std::getline(std::cin, date);

    if (type == "BMI") {
        std::cout<<"Enter value: ";
        std::cin>>value1;
        service.addAnalysis(type, date, value1);
    }
    else if (type == "BP") {
        std::cout<<"Enter systolic value(integer): ";
        std::cin>>value1;
        std::cout<<"Enter diastolic value(integer): ";
        std::cin>>value2;
        service.addAnalysis(type, date, value1, value2);
    }
}

void UI::displayAllAnalyses() {
    std::vector<MedicalAnalysis*> analyses = service.getAllAnalysis();
    for (auto analysis : analyses) {
        if (BMI* bmi = dynamic_cast<BMI*>(analysis)) {
            std::cout<<bmi->toString()<<std::endl;
        }
        else if (BP* bp = dynamic_cast<BP*>(analysis)) {
            std::cout<<bp->toString()<<std::endl;
        }
        else {
            std::cout<<"Unknown analysis type!"<<std::endl;
        }
    }
}

void UI::displayAnalysesByMonth() {
    int month;
    std::cout<<"Enter month: ";
    std::cin>>month;
    std::vector<MedicalAnalysis*> analyses = service.getAnalysesByMonth(month);
    for (auto analysis : analyses) {
        if (BMI* bmi = dynamic_cast<BMI*>(analysis)) {
            std::cout<<bmi->toString()<<std::endl;
        }
        else if (BP* bp = dynamic_cast<BP*>(analysis)) {
            std::cout<<bp->toString()<<std::endl;
        }
        else {
            std::cout<<"Unknown analysis type!"<<std::endl;
        }
    }
}

void UI::isIll() {
    int month;
    std::cout<<"Enter month: ";
    std::cin>>month;
    if (service.isIll(month)) {
        std::cout<<"The person is ill!"<<std::endl;
    }
    else {
        std::cout<<"The person is not ill!"<<std::endl;
    }
}

void UI::displayAnalysesBetweenDates() {
    std::string date1, date2;
    std::cout<<"Enter date1 (YYYY.MM.DD): ";
    std::getline(std::cin, date1);
    std::cout<<"Enter date2 (YYYY.MM.DD): ";
    std::getline(std::cin, date2);
    std::vector<MedicalAnalysis*> analyses = service.getAnalysesBetweenDates(date1, date2);
    for (auto analysis : analyses) {
        if (BMI* bmi = dynamic_cast<BMI*>(analysis)) {
            std::cout<<bmi->toString()<<std::endl;
        }
        else if (BP* bp = dynamic_cast<BP*>(analysis)) {
            std::cout<<bp->toString()<<std::endl;
        }
        else {
            std::cout<<"Unknown analysis type!"<<std::endl;
        }
    }
}

void UI::writeToFile() {
    std::string fileName, date1, date2;
    std::cout<<"Enter file name: ";
    std::getline(std::cin, fileName);
    std::cout<<"Enter date1 (YYYY.MM.DD): ";
    std::getline(std::cin, date1);
    std::cout<<"Enter date2 (YYYY.MM.DD): ";
    std::getline(std::cin, date2);
    service.writeToFile(fileName,date1,date2);
}

void UI::run() {
    while (true) {
        int option;
        displayMenu();
        std::cout<<"Enter option: ";
        std::cin>>option;
        std::cin.ignore();
        if (option == 0) {
            break;
        }
        switch (option) {
            case 1:
                addAnalysis();
                break;
            case 2:
                displayAllAnalyses();
                break;
            case 3:
                displayAnalysesByMonth();
                break;
            case 4:
                isIll();
                break;
            case 5:
                displayAnalysesBetweenDates();
                break;
            case 6:
                writeToFile();
                break;
            default:
                std::cout<<"Invalid option!"<<std::endl;
        }
    }
}
