//
// Created by balac on 6/17/2025.
//
#include <sstream>
#include "Astronomer.h"
Astronomer::Astronomer(std::string name, std::string constellation) :name(name), constellation(constellation){

}
std::string Astronomer::get_name() {
    return name;
}

std::string Astronomer::get_constellation() {
    return constellation;
}
void Astronomer::set_name(std::string name) {
    this->name = name;
}
void Astronomer::set_constellation(std::string constellation) {
    this->constellation = constellation;
}
std::string Astronomer::to_string() {
    return name+","+constellation+",";
}
bool Astronomer::operator==(Astronomer &other) {
    return name == other.name && constellation == other.constellation;
}

std::ostream& operator<<(std::ostream& os, Astronomer& a) {
    os<<a.to_string();
    return os;
}

std::istream& operator>>(std::istream& is, Astronomer& a) {
    std::string line;
    getline(is, line);
    if(line.empty()) return is;
    std::istringstream iss(line);
    getline(iss, a.name, ',');
    getline(iss, a.constellation, ',');
    return is;
}

