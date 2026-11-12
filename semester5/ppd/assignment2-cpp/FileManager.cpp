#pragma once

#include <fstream>
#include <sstream>
#include <string>

class FileManager {
public:
    //read matrix F and the convolution matrix from file
    static bool readFile(const std::string& filename, int*& f, int& n, int& m, int*& c, int& k) {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;

        // dimensions
        n = m = 0;
        int cRows = 0, cCols = 0;
        bool kernel = false; //becomes true after the empty line
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream tokens(line);
            int number;
            int count = 0;
            while (tokens >> number)
                count++;
            if (count == 0) {
                if (n > 0)
                    kernel = true;
                continue;
            }
            if (!kernel) {
                if (n == 0)
                    m = count;
                n++;
            } else {
                if (cRows == 0)
                    cCols = count;
                cRows++;
            }
        }
        if (n == 0 || cRows == 0 || cRows != cCols)
            return false;
        k = cRows;

        // numbers
        file.clear();
        file.seekg(0);
        f = new int[n * m];
        c = new int[k * k];
        for (int i = 0; i < n * m; i++) {
            if (!(file >> f[i]))
                return false;
        }
        for (int i = 0; i < k * k; i++) {
            if (!(file >> c[i]))
                return false;
        }
        return true;
    }

    //write matrix to file
    static bool writeFile(const std::string& filename, const int* data, int rows, int cols, bool append = false) {
        std::ofstream file(filename, append ? std::ios::app : std::ios::trunc);
        if (!file.is_open())
            return false;

        if (append)
            file << "\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                file << data[i * cols + j] << " ";
            file << "\n";
        }
        return true;
    }
};
