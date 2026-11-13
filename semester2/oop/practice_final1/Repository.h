//
// Created by balac on 6/15/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

#include "Department.h"
#include "Volunteer.h"


class Repository {
private:
    std::string filaneme1, filaneme2;
    std::vector<Department> departments;
    std::vector<Volunteer> volunteers;
public:
    Repository(std::string filaneme1, std::string filaneme2);
    void load();
    void save();
    std::vector<Department> get_departments_repo();
    std::vector<Volunteer> get_volunteers_repo();

    void append_volunteer(Volunteer volunteer);
    void updateDepartment(Volunteer volunteer,std::string departmentName);
};



#endif //REPOSITORY_H
