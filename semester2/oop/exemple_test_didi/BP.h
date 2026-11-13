//
// Created by David Berbecar on 01.05.2025.
//

#ifndef BP_H
#define BP_H
#include "MedicalAnalysis.h"


class BP : public MedicalAnalysis {
private:
    int systolicValue;
    int diastolicValue;
public:
    BP(std::string date, int systolicValue, int diastolicValue);
    ~BP() override;
    bool isResultOK() override;
    std::string toString();
};



#endif //BP_H
