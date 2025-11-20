//
// Created by balac on 5/29/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "repository.h"


class service {
private:
    repository &r;
public:
    service(repository &r);
    std::vector<Equation> get_equations_service();
    std::vector<Equation> sorted();
    void update_eq(double a, double b, double c, int index);
};



#endif //SERVICE_H
