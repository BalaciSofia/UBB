//
// Created by David Berbecar on 01.05.2025.
//

#include "Service.h"

#include "BMI.h"
#include "BP.h"

Service::Service(Person& person): person{person}
{

}
Service::~Service() = default;

void Service::addAnalysis(std::string type, std::string date, double value1, double value2) {
    if (type == "BMI") {
        BMI* analysis = new BMI(date,value1);
        this->person.addAnalysis(analysis);
    }
    else if (type == "BP") {
        BP* analysis = new BP(date, int(value1), int(value2));
        this->person.addAnalysis(analysis);
    }
}

std::vector<MedicalAnalysis*> Service::getAllAnalysis() {
    return this->person.getAllAnalyses();
}
std::vector<MedicalAnalysis*> Service::getAnalysesByMonth(int month) {
    return this->person.getAnalysesByMonth(month);
}
bool Service::isIll(int month) {
    return this->person.isIll(month);
}
std::vector<MedicalAnalysis*> Service::getAnalysesBetweenDates(std::string date1, std::string date2) {
    return this->person.getAnalysesBetweenDates(date1,date2);
}
void Service::writeToFile(std::string fileName, std::string date1, std::string date2) {
    this->person.writeToFile(fileName,date1,date2);
}
