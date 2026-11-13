//
// Created by balac on 6/15/2025.
//

#include "Department.h"
#include <sstream>
std::string Department::getName() {
    return this->name;
}
std::string Department::getDescription() {
    return this->description;
}
void Department::setName(std::string name) {
    this->name = name;
}
void Department::setDescription(std::string description) {
    this->description = description;
}
Department::Department(std::string name, std::string description) : name(name), description(description) {}

std::ostream& operator<<(std::ostream& os, Department& department) {
    os << department.name << "," << department.description;
    return os;
}

std::istream& operator>>(std::istream& is, Department& department) {
    std::string line;
    if (std::getline(is, line)) {
        std::stringstream ss(line);
        std::getline(ss, department.name, ',');
        std::getline(ss, department.description, ',');
    }
    return is;
}

std::string Department::toString() {
    return "Name: "+this->name + "Description: " + this->description;
}