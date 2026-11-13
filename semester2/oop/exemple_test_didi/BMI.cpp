//
// Created by David Berbecar on 01.05.2025.
//

#include "BMI.h"

BMI::BMI(std::string date, double value): MedicalAnalysis(date), value{value}
{

}

BMI::~BMI() = default;

bool BMI::isResultOK() {
    return this->value>=18.5 && this->value<=25;
}

std::string BMI::toString() {
    std::stringstream output;
    output<<"BMI | Date: "<<this->date<<" | Value: "<<this->value;
    if (this->isResultOK()) {
        output<<" | Result: OK";
    } else {
        output<<" | Result: NOT OK";
    }
    std::string result = output.str();
    return result;
}