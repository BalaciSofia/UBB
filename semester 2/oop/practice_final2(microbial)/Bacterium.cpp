//
// Created by balac on 6/15/2025.
//

#include "Bacterium.h"

#include <sstream>
Bacterium::Bacterium(std::string name,std::string species,int size, std::vector<std::string> diseases)
    :name(name), species(species), size(size), diseases(diseases) {}

std::string Bacterium::getName() {
    return name;
}

std::string Bacterium::getSpecies() {
    return species;
}

int Bacterium::getSize() {
    return size;
}

std::vector<std::string> Bacterium::getDiseases() {
    return diseases;
}

std::string Bacterium::toString() {
    std::string result = name + "," + species + "," + std::to_string(size) + ",";
    for (const auto& disease : diseases) {
        result += disease + ";";
    }
    return result;
}
bool Bacterium::operator==(Bacterium& other){
    return name == other.name && species == other.species;
}

std::istream& operator>>(std::istream& is, Bacterium& bacterium) {
    std::string line;
    getline(is, line);
    if(line.empty()) return is;
    std::istringstream iss(line);
    std::string token;

    std::getline(iss, bacterium.name, ',');
    std::getline(iss, bacterium.species, ',');
    std::getline(iss, token, ',');
    bacterium.size = std::stoi(token);
    while (std::getline(iss, token, ';')) {
        if (!token.empty()) {
            bacterium.diseases.push_back(token);
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os,Bacterium& bacterium) {
    os << bacterium.toString()+";";
    return os;
}