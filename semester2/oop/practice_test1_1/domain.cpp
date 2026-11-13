
#include "domain.h"

Station::Station(std::string location, std::string name, std::vector<std::string> sensors) {
    this->location = location;
    this->name = name;
    this->sensors = sensors;
}

//getters
std::string Station::getLocation() {
    return this->location;
}
std::string Station::getName() {
    return this->name;
}
std::vector<std::string> Station::getSensors() {
    return this->sensors;
}

//setters
void Station::setLocation(std::string location) {
    this->location=location;
}
void Station::setName(std::string name) {
    this->name=name;
}
void Station::setSensors(std::vector<std::string> sensors) {
    this->sensors=sensors;
}