//
// Created by David Berbecar on 01.05.2025.
//

#ifndef MEDICALANALYSIS_H
#define MEDICALANALYSIS_H
#include <string>
#include <sstream>


class MedicalAnalysis {
protected:
    std::string date;
public:
    MedicalAnalysis(std::string date);
    virtual ~MedicalAnalysis() = default;
    virtual bool isResultOK() = 0;
    std::string getDate(){return date;};
    std::string toString();
};



#endif //MEDICALANALYSIS_H
