#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "FileManager.cpp"
using namespace std;

const string DATA_FILE = "date.txt";
const string EXPECTED_FILE = "expectedResult.txt";
const string OUTPUT_FILE = "output.txt";

//reads matrix F and the convolution matrix from the data file
bool readData(int*& f, int& n, int& m, int*& c, int& k) {
    if (!FileManager::readFile(DATA_FILE, f, n, m, c, k)) {
        cerr << "Error reading " << DATA_FILE << " (it must contain matrix F, an empty line and the convolution matrix)" << endl;
        return false;
    }
    if (k != 3) {
        cerr << "The convolution matrix from " << DATA_FILE << " is " << k << "x" << k << " but it must be 3x3" << endl;
        return false;
    }
    return true;
}

bool writeOutput(const string& filename, const int* v, int n, int m) {
    if (!FileManager::writeFile(filename, v, n, m)) {
        cerr << "Error writing " << filename << endl;
        return false;
    }
    return true;
}

//compares the computed matrix with the matrix from the file
bool isResultOk(const string& filename, int* v, int n, int m) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return false;
    }

    int expected;
    for (int i = 0; i < n * m; i++) {
        if (!(file >> expected) || expected != v[i]) {
            cerr << "Error: the computed result is different from " << filename << endl;
            return false;
        }
    }
    if (file >> expected) {
        cerr << "Error: " << filename << " has more numbers than the computed result" << endl;
        return false;
    }
    return true;
}
