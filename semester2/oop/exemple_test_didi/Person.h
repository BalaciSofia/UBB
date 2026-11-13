//
// Created by David Berbecar on 01.05.2025.
//

#ifndef PERSON_H
#define PERSON_H
#include <string>
#include<fstream>
#include <vector>

#include "MedicalAnalysis.h"


class Person {
private:
    std::string name;
    std::vector<MedicalAnalysis*> analyses;
public:
    Person(const std::string &name);
    ~Person();
    void addAnalysis(MedicalAnalysis* analysis);
    std::vector<MedicalAnalysis*> getAllAnalyses();
    std::vector<MedicalAnalysis*> getAnalysesByMonth(int month);
    bool isIll(int month);
    std::vector<MedicalAnalysis*> getAnalysesBetweenDates(std::string date1, std::string date2);
    void writeToFile(std::string filename, std::string date1, std::string date2);
};



#endif //PERSON_H
