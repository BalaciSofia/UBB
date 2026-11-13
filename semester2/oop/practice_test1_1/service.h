#pragma once
#include "repo.h"

class Service {
private:
    Repository &repo;
    public:
    Service(Repository &repo);
    ~Service()=default;
    void add_station_serv(std::string location,std::string name,std::vector<std::string> sensors);
    DynamicArray<Station> &get_station_serv();
    void initialize();
    void test_add_station_serv();
    std::vector<std::string> locations();
    int count(std::string sensor,std::string location);
};
