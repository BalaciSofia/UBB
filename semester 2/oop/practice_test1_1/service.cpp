
#include "service.h"
#include "domain.h"
#include <cassert>

Service::Service(Repository &repo): repo(repo) {}
void Service::add_station_serv(std::string location,std::string name,std::vector<std::string> sensors) {
    /*
     *adds a station to the repository
     *param1:location:location of the station
     *param2:name:name of the station
     *param3:sensors:sensors the station has
     */
    Station s=Station(location,name,sensors);
    this->repo.add_station_repo(s);
}
DynamicArray<Station>& Service::get_station_serv() {
    return this->repo.get_stations_repo();
}

void Service::initialize() {
    add_station_serv("New York", "Central Park", std::vector<std::string>{"Thermometer", "Barometer"});
    add_station_serv("New York", "JFK Airport", std::vector<std::string>{"Thermometer", "Anemometer", "Wind Vane"});
    add_station_serv("London", "Heathrow Airport", std::vector<std::string>{"Thermometer", "Anemometer", "Wind Vane", "Hygrometer"});
    add_station_serv("London", "Greenwich", std::vector<std::string>{"Hygrometer", "Rain Gauge"});
    add_station_serv("Cluj", "Cetatuie", std::vector<std::string>{"Thermometer", "Barometer"});
}

void Service::test_add_station_serv() {
    Repository repo = Repository();
    Service service = Service(repo);
    service.add_station_serv("me","you",std::vector<std::string>{"T", "B"});
    assert(service.get_station_serv().getSize()==1);
    assert(service.get_station_serv()[0].getLocation()=="me");
    assert(service.get_station_serv()[0].getName()=="you");
    assert(service.get_station_serv()[0].getSensors().size()==2);
    assert(service.get_station_serv()[0].getSensors()[0]=="T");
    assert(service.get_station_serv()[0].getSensors()[1]=="B");
}

std::vector<std::string> Service::locations() {
    /*
     *returns a vector containing all the locations in the repo
     */
    std::vector<std::string> locations;
    for (int i=0;i<this->get_station_serv().getSize();i++) {
        int found=0;
        for (int j=0;j<locations.size();j++) {
            if (locations[j]==this->get_station_serv()[i].getLocation()) {
                found=1;
            }
        }
        if (found==0) {
            locations.push_back(this->get_station_serv()[i].getLocation());
        }
    }
    return locations;
}

int Service::count(std::string sensor,std::string location) {
    /*
     *counts how many sensors of a given type a given location has
     */
    int c=0;
    for (int i=0;i<this->get_station_serv().getSize();i++) {
        if (this->get_station_serv()[i].getLocation()==location) {
            for (int j=0;j<this->get_station_serv()[i].getSensors().size();j++) {
                if (this->get_station_serv()[i].getSensors()[j]==sensor) {
                    c++;
                }
            }
        }
    }
    return c;
}