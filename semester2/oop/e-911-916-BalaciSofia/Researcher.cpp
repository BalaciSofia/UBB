//
// Created by balac on 6/17/2025.
//
#include <sstream>
#include "Researcher.h"
Researcher::Researcher(std::string name,std::string position):name(name),position(position){

}

std::string Researcher::getName() {
    return name;
}

std::string Researcher::getPosition() {
    return position;
}

void Researcher::setName(std::string name) {
    this->name=name;
}

void Researcher::setPosition(std::string position) {
    this->position=position;
}

std::string Researcher::toString() {
    return name+","+position+",";
}

std::istream &operator>>(std::istream &is, Researcher &r) {
    std::string line;
    getline(is, line);
    if(line.empty()) return is;
    std::istringstream iss(line);

    getline(iss, r.name, ',');
    getline(iss, r.position, ',');
    return is;
}

std::ostream &operator<<(std::ostream &os, Researcher &r) {
    os<<r.toString()+',';
}
























//     //doubles
//     std::string longitude, latitude;
//     getline(iss, longitude, ',');
//     getline(iss, latitude, ',');
//     event.location.first = std::stod(longitude);
//     event.location.second = std::stod(latitude);
//     return is;
// }
