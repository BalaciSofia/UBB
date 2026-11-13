//
// Created by balac on 6/17/2025.
//

#include "Star.h"
#include <sstream>

Star::Star(std::string name, std::string constellation, int ra, int dec, int diameter):name(name),
constellation(constellation),ra(ra),dec(dec),diameter(diameter){

}

std::string Star::get_name() {
    return name;
}
std::string Star::get_constellation() {
    return constellation;
}
int Star::get_ra() {
    return ra;
}
int Star::get_dec() {
    return dec;
}
int Star::get_diameter() {
    return diameter;
}

void Star::set_name(std::string name) {
    this->name = name;
}

void Star::set_constellation(std::string constellation) {
    this->constellation = constellation;
}

void Star::set_ra(int ra) {
    this->ra = ra;
}

void Star::set_dec(int dec) {
    this->dec = dec;
}

void Star::set_diameter(int diameter) {
    this->diameter = diameter;
}

std::string Star::to_string() {
    return name+","+constellation+","+std::to_string(ra)+","+std::to_string(dec)+","+std::to_string(diameter)+",";
}

std::ostream& operator<<(std::ostream& os, Star& star) {
    return os<<star.to_string();
}

std::istream& operator>>(std::istream& is, Star& star) {
    std::string line;
    getline(is, line);
    if(line.empty()) return is;
    std::istringstream iss(line);

    std::string name,constellation,ra,dec,diameter;
    getline(iss, name, ',');
    getline(iss, constellation, ',');
    getline(iss,ra,',');
    getline(iss,dec,',');
    getline(iss,diameter,',');

    star.set_name(name);
    star.set_constellation(constellation);
    star.set_ra(stoi(ra));
    star.set_dec(stoi(dec));
    star.set_diameter(stoi(diameter));

    return is;
}