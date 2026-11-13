//
// Created by balac on 6/15/2025.
//

#include "Biologist.h"
#include <sstream>
Biologist::Biologist(std::string name, std::vector<std::string> bacterialSpecies) :name(name),bacterialSpecies(bacterialSpecies){
}

std::string Biologist::getName() {
    return name;
}

std::vector<std::string> Biologist::getBacterialSpecies() {
    return bacterialSpecies;
}

void Biologist::setName(std::string name) {
    this->name = name;
}

void Biologist::setBacterialSpecies(std::vector<std::string> bactSpecies) {
    this->bacterialSpecies = bactSpecies;
}

bool Biologist::operator==(Biologist &other){
    return this->name == other.name && this->bacterialSpecies == other.bacterialSpecies;
}
std::string Biologist::toString() {
    std::string result = name + ",";
    for (auto &species : bacterialSpecies) {
        result += species + " ";
    }
    return result;
}

std::ostream &operator<<(std::ostream &os,Biologist &bio) {
    os<<bio.toString()+",";
    return os;
}

std::istream &operator>>(std::istream &is,Biologist &bio) {
    std::string line;
    getline(is, line);

    if(line.empty()) return is;

    std::istringstream iss(line);
    getline(iss, bio.name, ',');

    std::string tokens;
    getline(iss, tokens, ',');
    std::istringstream iss2(tokens);
    std::string bacteria;
    while (getline(iss2, bacteria, ';')) {
        bio.bacterialSpecies.push_back(bacteria);
    }
    return is;
}