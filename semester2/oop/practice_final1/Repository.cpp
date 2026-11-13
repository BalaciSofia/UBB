//
// Created by balac on 6/15/2025.
//

#include "Repository.h"
#include <fstream>

Repository::Repository(std::string filaneme1, std::string filaneme2):filaneme1(filaneme1), filaneme2(filaneme2) {
    this->load();
}

void Repository::load() {
    std::ifstream file1(filaneme1);
    if (!file1.is_open()) {
        throw std::runtime_error("Could not open file: " + filaneme1);
    }
    Department department;
    while (file1 >> department) {
        departments.push_back(department);
    }
    file1.close();

    std::ifstream file2(filaneme2);
    if (!file2.is_open()) {
        throw std::runtime_error("Could not open file: " + filaneme2);
    }
    Volunteer volunteer;
    while (file2 >> volunteer) {
        volunteers.push_back(volunteer);
    }
    file2.close();
}

void Repository::save() {
    std::ofstream file2(filaneme2);
    if (!file2.is_open()) {
        throw std::runtime_error("Could not open file: " + filaneme2);
    }
    for (auto& volunteer : volunteers) {
        file2 << volunteer;
    }
    file2.close();
}

std::vector<Department> Repository::get_departments_repo() {
    return departments;
}

std::vector<Volunteer> Repository::get_volunteers_repo() {
    return volunteers;
}

void Repository::append_volunteer(Volunteer volunteer) {
    volunteers.push_back(volunteer);
    this->save();
}

void Repository::updateDepartment(Volunteer volunteer, std::string departmentName) {
    for (auto& vol : volunteers) {
        if (vol.getName() == volunteer.getName()) {
            vol.setDepartment(departmentName);
            break;
        }
    }
    this->save();
}