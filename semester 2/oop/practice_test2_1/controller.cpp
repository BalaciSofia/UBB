//
// Created by balac on 5/8/2025.
//

#include "controller.h"

#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <fstream>
#include "Block.h"
#include "House.h"

void Controller::add_Building_house(std::string address, int year, std::string type, bool isHistorical) {
    /*
     *adds a new house to the list of buildings
     *parameters:address=address of house, year=year of construction,
     *type, isHistorical=true if the house is historical
     */
    for (auto building : this->buildings) {
        if (building->getAddress() == address && building->getYear() == year) {
            throw std::logic_error("Building already exists!");
        }
    }
    House* h=new House(address, year, type, isHistorical);
    this->buildings.push_back(h);
}

void Controller::add_Building_block(std::string address, int year, int total_apartments, int occupied_apartments) {
    /*
     *adds a new block to the list of buildings
     *parameters:address=address of block, year=year of construction,
     *total_apartments=total number of apartments, occupied_apartments=number of occupied apartments
     */
    for (auto building : this->buildings) {
        if (building->getAddress() == address && building->getYear() == year) {
            throw std::logic_error("Building already exists!");
        }
    }
    Block* b=new Block(address, year, total_apartments, occupied_apartments);
    this->buildings.push_back(b);
}

std::vector<Building*> Controller::get_all_buildings() {
    return this->buildings;
}

std::vector<Building*> Controller::get_all_buildings_sorted() {
    /*
     *returns the list of buildings sorted by year
     */
    std::vector<Building*> buildings = this->buildings;
    std::sort(buildings.begin(), buildings.end(), [](Building* a, Building* b) {;
        return a->getYear() < b->getYear();
    });
    return buildings;
}

std::vector<Building*> Controller::getAllToBeRestored() {
    std::vector<Building*> result;
    for (auto building : this->buildings) {
        if (building->mustBeRestored()) {
            result.push_back(building);
        }
    }
    return result;
}

std::vector<Building*> Controller::getAllToBeDemolished() {
    std::vector<Building*> result;
    for (auto building : this->buildings) {
        if (building->mustBeDemolished()) {
            result.push_back(building);
        }
    }
    return result;
}

void Controller::writeToFile(std::string filename1, std::string filename2) {
    std::ofstream file1(filename1);
    std::ofstream file2(filename2);
    if (!file1.is_open() || !file2.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    file1 << " Buildings to be restored:\n";
    file2 << " Buildings to be demolished:\n";
    for (auto building : this->buildings) {
        if (building->mustBeRestored()) {
            file1 << building->toString() << std::endl;
        }
        if (building->mustBeDemolished()) {
            file2 << building->toString() << std::endl;
        }
    }
    file1.close();
    file2.close();
}
#include <cassert>
#include <iostream>
void Controller:: testadd() {
    Controller c;
    // Test adding a house
    c.add_Building_house("Street 1", 2000, "Type A", true);
    assert(c.get_all_buildings().size() == 1);
    assert(c.get_all_buildings()[0]->getAddress() == "Street 1");
    assert(c.get_all_buildings()[0]->getYear() == 2000);

    // Test adding a block
    c.add_Building_block("Street 2", 2010, 20, 15);
    assert(c.get_all_buildings().size() == 2);
    assert(c.get_all_buildings()[1]->getAddress() == "Street 2");
    assert(c.get_all_buildings()[1]->getYear() == 2010);

    // Test duplicate house
    try {
        c.add_Building_house("Street 1", 2000, "Type A", true);
        assert(false); // Should not reach here
    } catch (const std::logic_error &e) {
        assert(std::string(e.what()) == "Building already exists!");
    }

    // Test duplicate block
    try {
        c.add_Building_block("Street 2", 2010, 20, 15);
        assert(false); // Should not reach here
    } catch (const std::logic_error &e) {
        assert(std::string(e.what()) == "Building already exists!");
    }

    std::cout << "Add tests passed!\n";
}
void Controller:: testsort() {
    Controller c;
    // Add buildings
    c.add_Building_house("Street 1", 2000, "Type A", true);
    c.add_Building_block("Street 2", 2010, 20, 15);
    c.add_Building_house("Street 3", 1995, "Type B", false);

    // Get sorted buildings
    std::vector<Building*> sortedBuildings = c.get_all_buildings_sorted();

    // Verify sorting by year
    assert(sortedBuildings.size() == 3);
    assert(sortedBuildings[0]->getYear() == 1995);
    assert(sortedBuildings[1]->getYear() == 2000);
    assert(sortedBuildings[2]->getYear() == 2010);

    std::cout << "Sorting test passed!\n";
}