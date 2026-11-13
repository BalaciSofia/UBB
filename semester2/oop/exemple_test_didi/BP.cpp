//
// Created by David Berbecar on 01.05.2025.
//

#include "BP.h"

BP::BP(std::string date, int systolicValue, int diastolicValue):MedicalAnalysis(date), systolicValue{systolicValue}, diastolicValue{diastolicValue}
{

}

BP::~BP() = default;

bool BP::isResultOK() {
    return this->systolicValue>=90 && this->systolicValue<=119 && this->diastolicValue>=60 && this->diastolicValue<=79;
}

std::string BP::toString() {
    std::stringstream output;
    output<<"BP | Date: "<<this->date<<" | Systolic Value: "<<this->systolicValue<<" | Diastolic Value: "<<this->diastolicValue;
    if (this->isResultOK()) {
        output<<" | Result: OK";
    } else {
        output<<" | Result: NOT OK";
    }
    std::string result = output.str();
    return result;
}
