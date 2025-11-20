//
// Created by balac on 6/15/2025.
//

#include "Volunteer.h"
#include <sstream>
#include <iostream>
Volunteer::Volunteer(std::string name, std::string email, std::string interests, std::string department)
:name(name),email(email),interests(interests),department(department) {}

Volunteer::Volunteer(std::string name, std::string email, std::string interests)
:name(name), email(email), interests(interests) ,department("") {}

std::string Volunteer::getName() {
    return this->name;
}
std::string Volunteer::getEmail() {
    return this->email;
}
std::string Volunteer::getInterests() {
    return this->interests;
}
std::string Volunteer::getDepartment() {
    return this->department;
}
void Volunteer::setName(std::string name) {
    this->name = name;
}
void Volunteer::setEmail(std::string email) {
    this->email = email;
}
void Volunteer::setInterests(std::string interests) {
    this->interests = interests;
}
void Volunteer::setDepartment(std::string department) {
    this->department = department;
}

std::string Volunteer::toString() {
    return getName()+","+getEmail()+","+getInterests();
}

std::ostream& operator<<(std::ostream& os, Volunteer& volunteer) {
    os << volunteer.name << "," << volunteer.email<< "," << volunteer.interests << "," << volunteer.department << ","<<"\n";
    return os;
}

std::istream& operator>>(std::istream& is, Volunteer& volunteer) {
    std::string name, email, interest, department;
    std::vector<std::string> interests;
    if(is.peek() == '\n') is.ignore();
    std::string str;
    std::getline(is, str);
    if(str.empty()) return is;
    std::istringstream iss(str);
    std::getline(iss, name, ',');
    std::getline(iss, email, ',');
    std::getline(iss, interest, ',');
    std::getline(iss, department, ',');
    volunteer.name = name;
    volunteer.email = email;
    volunteer.interests = interest;
    volunteer.department = department;
    return is;
}

