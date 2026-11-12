#pragma once

#include <fstream>
#include <sstream>
#include <string>

class FileManager {
public:
    static bool readDimensions(const std::string& filename, int& rows, int& cols) {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;

        rows = 0;
        cols = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream tokens(line);
            int number;
            int count = 0;
            while (tokens >> number)
                count++;
            if (count == 0)
                continue;
            if (rows == 0)
                cols = count;
            rows++;
        }
        return true;
    }

    //read matrix from file
    static bool readFile(const std::string& filename, int* data, int rows, int cols) {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;

        for (int i = 0; i < rows * cols; i++) {
            if (!(file >> data[i]))
                return false;
        }
        return true;
    }

    //write matrix to file
    static bool writeFile(const std::string& filename, const int* data, int rows, int cols) {
        std::ofstream file(filename);
        if (!file.is_open())
            return false;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                file << data[i * cols + j] << " ";
            file << "\n";
        }
        return true;
    }
};
