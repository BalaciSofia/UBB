#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include "../common/FileManager.cpp"
using namespace std;

const string MATRIX_F_FILE = "MatrixF.txt";
const string CONVOLUTION_FILE = "ConvolutionM.txt";
const string EXPECTED_FILE = "expectedResult.txt";
const string OUTPUT_FILE = "output.txt";

bool readMatrixF(int*& f, int& n, int& m) {
    if (!FileManager::readDimensions(MATRIX_F_FILE, n, m)) {
        cerr << "Error opening " << MATRIX_F_FILE << endl;
        return false;
    }
    if (n <= 0 || m <= 0) {
        cerr << MATRIX_F_FILE << " is empty" << endl;
        return false;
    }
    f = new int[n * m];
    if (!FileManager::readFile(MATRIX_F_FILE, f, n, m)) {
        cerr << "Error reading " << MATRIX_F_FILE << endl;
        return false;
    }
    return true;
}

bool readConvolutionMatrix(int*& c, int& k) {
    int rows, cols;
    if (!FileManager::readDimensions(CONVOLUTION_FILE, rows, cols)) {
        cerr << "Error opening " << CONVOLUTION_FILE << endl;
        return false;
    }
    if (rows != cols || rows <= 0 || rows % 2 == 0) {
        cerr << CONVOLUTION_FILE << " is " << rows << "x" << cols << " but it must be square with an odd size" << endl;
        return false;
    }
    k = rows;
    c = new int[k * k];
    if (!FileManager::readFile(CONVOLUTION_FILE, c, k, k)) {
        cerr << "Error reading " << CONVOLUTION_FILE << endl;
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
    int rows, cols;
    if (!FileManager::readDimensions(filename, rows, cols)) {
        cerr << "Error opening " << filename << endl;
        return false;
    }
    if (rows != n || cols != m) {
        cerr << filename << " is " << rows << "x" << cols << " but the computed result is " << n << "x" << m << endl;
        return false;
    }
    int* expected = new int[n * m];
    if (!FileManager::readFile(filename, expected, n, m)) {
        cerr << "Error reading " << filename << endl;
        delete[] expected;
        return false;
    }

    bool ok = equal(v, v + n * m, expected);
    if (!ok) {
        cerr << "Error: the computed result is different from " << filename << endl;
    }
    delete[] expected;
    return ok;
}
