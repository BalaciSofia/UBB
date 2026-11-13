//
// Created by David Berbecar on 01.05.2025.
//

#ifndef BMI_H
#define BMI_H
#include "MedicalAnalysis.h"


class BMI : public MedicalAnalysis  {
private:
    double value;
public:
    BMI(std::string date,double value);
    ~BMI() override;
    bool isResultOK() override ;
    std::string toString();
};



#endif //BMI_H
