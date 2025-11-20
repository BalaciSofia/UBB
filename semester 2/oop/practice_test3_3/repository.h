//
// Created by balac on 5/29/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "Equation.h"
#include <vector>
#include <string>

class repository {
private:
    std::vector<Equation> equations;
    std::string filename;
public:
    repository(std::string filename);
    std::vector<Equation> get_equations_repo();
    std::string get_filename();
    void load();
    void update(double a, double b, double c, int index);
};



#endif //REPOSITORY_H
