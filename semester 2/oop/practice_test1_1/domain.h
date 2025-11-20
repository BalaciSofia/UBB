#pragma once
#include <string>
#include <vector>

class Station {
private:
    std::string location;
    std::string name;
    std::vector<std::string> sensors;
    public:
    Station(std::string location, std::string name, std::vector<std::string> sensors);
    Station()= default;
    ~Station() = default;

    //getters
    std::string getLocation();
    std::string getName();
    std::vector<std::string> getSensors();

    //setters
    void setLocation(std::string location);
    void setName(std::string name);
    void setSensors(std::vector<std::string> sensors);
};
