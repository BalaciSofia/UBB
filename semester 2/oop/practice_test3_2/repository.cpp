//
// Created by balac on 5/29/2025.
//

#include "repository.h"
#include <fstream>

repository::repository(std::string filename): filename(filename) {
    this->traingles = new std::vector<triangle>;
    this->load();
}

void repository::load() {
    std::ifstream file(this->filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + this->filename);
    }
    triangle t(0, 0, 0);
    while (file >> t) {
        this->traingles->push_back(t);
    }
    file.close();
}

void repository::save() {
    std::ofstream file(this->filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + this->filename);
    }
    for (const triangle &t : *this->traingles) {
        file << t << std::endl;
    }
    file.close();
}

std::vector<triangle> *repository::get_triangles_repo() {
    return this->traingles;
}