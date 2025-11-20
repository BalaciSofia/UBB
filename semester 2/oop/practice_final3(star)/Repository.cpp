//
// Created by balac on 6/17/2025.
//

#include "Repository.h"
#include <fstream>
Repository::Repository(std::string filename1, std::string filename2):filename1(filename1),filename2(filename2) {
    this->load();
}
void Repository::load() {
    std::ifstream file1(filename1);
    if (!file1.is_open()) {
        throw std::runtime_error("Could not open file: " + filename1);
    }
    Astronomer a;
    while (file1 >> a) {
        astronomers.push_back(a);
    }
    file1.close();
    std::ifstream file2(filename2);
    if (!file2.is_open()) {
        throw std::runtime_error("Could not open file: " + filename2);
    }
    Star s;
    while (file2 >> s) {
        stars.push_back(s);
    }
    file2.close();
}

void Repository::save() {
    std::ofstream file2(filename2);
    if (!file2.is_open()) {
        throw std::runtime_error("Could not open file: " + filename2);
    }
    for (auto& star : stars) {
        file2 << star;
    }
    file2.close();
}

std::vector<Astronomer> Repository::get_astronomers() {
    return astronomers;
}

std::vector<Star> Repository::get_stars() {
    return stars;
}