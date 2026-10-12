//
// Created by balac on 10/1/2026.
//

#include "FileManager.h"

#include <fstream>
#include <string>


std::vector<double> FileManager::readFile(std::string filename) {
    std::ifstream file(filename);
    std::vector<double> result;
    if (!file.is_open())
        return {};
    double number;
    while (file >> number) {
        result.push_back(number);
    }
    return result;
}

void FileManager::writeFile(std::string filename, std::vector<double> result) {
    std::ofstream file(filename);
    if (!file.is_open())
        return;
    for (auto number : result) {
        file << number << " ";
    }
}