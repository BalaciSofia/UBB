//
// Created by balac on 6/16/2025.
//

#include "Repository.h"

#include <fstream>
Repository::Repository(std::string filename1, std::string filename2) : filename1(filename1), filename2(filename2) {
    this->load();
}
void Repository::load() {
    std::ifstream file1(filename1);
    if (!file1.is_open()) {
        throw std::runtime_error("Could not open file: " + filename1);
    }
    Biologist biologist;
    while (file1 >> biologist) {
        biologists.push_back(biologist);
    }
    file1.close();

    std::ifstream file2(filename2);
    if (!file2.is_open()) {
        throw std::runtime_error("Could not open file: " + filename2);
    }
    Bacterium bacterium;
    while (file2 >> bacterium) {
        bacteriums.push_back(bacterium);
    }
    file2.close();
}

void Repository::save() {
    std::ofstream file2(filename2);
    if (!file2.is_open()) {
        throw std::runtime_error("Could not open file: " + filename2);
    }
    for (auto& bacterium : bacteriums) {
        file2 << bacterium<<"\n";
    }
    file2.close();
}
std::vector<Biologist> Repository::get_biologists_repo() {
    return biologists;
}
std::vector<Bacterium> Repository::get_bacteriums_repo() {
    return bacteriums;
}
void Repository::append_bacterium(Bacterium bacterium) {
    for (auto &b:this->bacteriums) {
        if (b == bacterium) {
            throw std::runtime_error("Bacterium already exists in the repository.");
        }
    }
    bacteriums.push_back(bacterium);
    this->save();
}