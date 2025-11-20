
#include "repo.h"

void Repository::add_station_repo(Station station) {
    /*
     *adds a station to the repository
     *param:the station object
     */
    if (search_station_repo(station)==true)
        throw std::logic_error("Station already exists");
    this->stations.append(station);
}
bool Repository::search_station_repo(Station station) {
    for (int i=0;i<this->stations.getSize();i++) {
        if (this->stations[i].getName()==station.getName() && this->stations[i].getLocation()==station.getLocation())
            return true;//found
    }
    return false;
}
DynamicArray<Station>& Repository:: get_stations_repo() {
    return this->stations;
}
#include <cassert>
void Repository::test_add_station_repo() {
    Repository repo = Repository();
    repo.add_station_repo(Station("me","you",std::vector<std::string>{"T", "B"}));
    assert(repo.get_stations_repo().getSize()==1);
    assert(repo.get_stations_repo()[0].getLocation()=="me");
    assert(repo.get_stations_repo()[0].getName()=="you");
    assert(repo.get_stations_repo()[0].getSensors().size()==2);
    assert(repo.get_stations_repo()[0].getSensors()[0]=="T");
    assert(repo.get_stations_repo()[0].getSensors()[1]=="B");
}
