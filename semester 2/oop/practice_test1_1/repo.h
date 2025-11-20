#pragma once
#include "domain.h"
#include "dynamicarray.h"

class Repository {
private:
    DynamicArray<Station> stations;
    public:
    Repository()=default;

    void add_station_repo(Station station);
    bool search_station_repo(Station station);
    DynamicArray<Station>& get_stations_repo();
    void test_add_station_repo();
};
