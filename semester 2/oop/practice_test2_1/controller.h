//
// Created by balac on 5/8/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>

#include "Building.h"


class Controller {
private:
    std::vector<Building*> buildings;
public:
    Controller()=default;
    void add_Building_house(std::string address, int year, std::string type, bool isHistorical);
    void add_Building_block(std::string address, int year, int total_apartments, int occupied_apartments);
    std::vector<Building*> get_all_buildings();
    std::vector<Building*> get_all_buildings_sorted();
    std::vector<Building*> getAllToBeRestored();
    std::vector<Building*> getAllToBeDemolished();
    void writeToFile(std::string filename1, std::string filename2);
    void testadd();
    void testsort();
};



#endif //CONTROLLER_H
