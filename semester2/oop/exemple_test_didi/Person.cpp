//
// Created by David Berbecar on 01.05.2025.
//

#include "Person.h"

#include "BMI.h"
#include "BP.h"

Person::Person(const std::string &name): name{name}
{

}
Person::~Person() {
    for (auto analysis : this->analyses) {
        delete analysis;
    }
}

void Person::addAnalysis(MedicalAnalysis* analysis) {
    this->analyses.push_back(analysis);
}

std::vector<MedicalAnalysis *> Person::getAllAnalyses() {
    return this->analyses;
}

std::vector<MedicalAnalysis*> Person::getAnalysesByMonth(int month) {
    std::vector<MedicalAnalysis*> result;
    for (auto analysis : this->analyses) {
        if (std::stoi(analysis->getDate().substr(5,2)) == month) {
            result.push_back(analysis);
        }
    }
    return result;
}

bool Person :: isIll(int month) {
    for (auto analysis : this->analyses) {
        if (std::stoi(analysis->getDate().substr(5,2)) == month) {
            if (analysis->isResultOK() == true) {
                return false;
            }
        }
    }
    return true;
}

std::vector<MedicalAnalysis*> Person::getAnalysesBetweenDates(std::string date1, std::string date2) {
    std::vector<MedicalAnalysis*> result;
    for (auto analysis: this->analyses) {
        if (analysis->getDate() >= date1 && analysis->getDate() <= date2) {
            result.push_back(analysis);
        }
    }
    return result;
}

void Person::writeToFile(std::string filename, std::string date1, std::string date2) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Could not open file ");
    }
    std::vector<MedicalAnalysis*> analyses = this->getAnalysesBetweenDates(date1, date2);
    for (auto analysis : analyses) {
        if (BMI* bmi = dynamic_cast<BMI*>(analysis)) {
            out<<bmi->toString()<<std::endl;
        }
        else if (BP* bp = dynamic_cast<BP*>(analysis)) {
            out<<bp->toString()<<std::endl;
        }
    }
}