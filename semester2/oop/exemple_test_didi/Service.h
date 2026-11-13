//
// Created by David Berbecar on 01.05.2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "Person.h"


class Service {
private:
    Person& person;
public:
    Service(Person& person);
    ~Service();
    void addAnalysis(std::string type, std::string date, double value1, double value2=-1);
    std::vector<MedicalAnalysis*> getAllAnalysis();
    std::vector<MedicalAnalysis*> getAnalysesByMonth(int month);
    bool isIll(int month);
    std::vector<MedicalAnalysis*> getAnalysesBetweenDates(std::string date1, std::string date2);
    void writeToFile(std::string fileName, std::string date1, std::string date2);
};



#endif //SERVICE_H
