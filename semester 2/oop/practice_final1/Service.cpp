//
// Created by balac on 6/15/2025.
//

#include "Service.h"

#include <algorithm>
#include <bits/ranges_algo.h>

std::vector<Department> Service::get_departments_service() {
    return this->repo.get_departments_repo();
}
std::vector<Volunteer> Service::get_volunteers_service() {
    return this->repo.get_volunteers_repo();
}

std::vector<Volunteer> Service::volunteersForDepartment(Department department) {
    std::vector<Volunteer> volunteers;
    for (auto & vol:this->get_volunteers_service()) {
        if (department.getName() == vol.getDepartment()) {
            volunteers.push_back(vol);
        }
    }
    //sort by name
    std::sort(volunteers.begin(), volunteers.end(), [](Volunteer &a,Volunteer &b) {
        return a.getName() < b.getName();
    });
    return volunteers;
}

std::vector<Volunteer> Service::volunteersUnassigned() {
    std::vector<Volunteer> volunteers;
    for (auto & vol:this->get_volunteers_service()) {
        if (vol.getDepartment()=="") {
            volunteers.push_back(vol);
        }
    }
    return volunteers;
}

void Service::addVolunteer(std::string name, std::string email, std::string interests) {
    Volunteer vol(name, email, interests);
    this->repo.append_volunteer(vol);
    this->notifyObservers();
}

void Service::assignVolunteer(Volunteer volunteer, Department dep) {
    this->repo.updateDepartment(volunteer, dep.getName());
    this->notifyObservers();
}

int Service::numberofvolunteers(Department department) {
    int count = 0;
    for (auto &vol:this->get_volunteers_service()) {
        if (department.getName() == vol.getDepartment()) {
            count++;
        }
    }
    return count;
}
