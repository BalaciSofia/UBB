//
// Created by David Berbecar on 01.05.2025.
//

#include "MedicalAnalysis.h"

MedicalAnalysis::MedicalAnalysis(std::string date): date{date}
{

}


std::string MedicalAnalysis::toString() {
    std::stringstream output;
    output<<this->date;
    std::string result = output.str();
    return result;
}