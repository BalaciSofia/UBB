#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include "../common/FileManager.cpp"
#include "Convolution.cpp"
using namespace std;

const string MATRIX_F_FILE = "MatrixF.txt";
const string CONVOLUTION_FILE = "ConvolutionM.txt";
const string EXPECTED_FILE = "expectedResult.txt";
const string OUTPUT_FILE = "output.txt";

bool readMatrixF(int f[N][M], int n, int m) {
    int rows, cols;
    if (!FileManager::readDimensions(MATRIX_F_FILE, rows, cols)) {
        cerr << "Error opening " << MATRIX_F_FILE << endl;
        return false;
    }
    if (rows != n || cols != m) {
        cerr << MATRIX_F_FILE << " is " << rows << "x" << cols << " but the static array is " << n << "x" << m << endl;
        return false;
    }
    if (!FileManager::readFile(MATRIX_F_FILE, &f[0][0], n, m)) {
        cerr << "Error reading " << MATRIX_F_FILE << endl;
        return false;
    }
    return true;
}

bool readConvolutionMatrix(int c[K][K], int k) {
    int rows, cols;
    if (!FileManager::readDimensions(CONVOLUTION_FILE, rows, cols)) {
        cerr << "Error opening " << CONVOLUTION_FILE << endl;
        return false;
    }
    if (rows != k || cols != k) {
        cerr << CONVOLUTION_FILE << " is " << rows << "x" << cols << " but the static array is " << k << "x" << k << endl;
        return false;
    }
    if (!FileManager::readFile(CONVOLUTION_FILE, &c[0][0], k, k)) {
        cerr << "Error reading " << CONVOLUTION_FILE << endl;
        return false;
    }
    return true;
}

bool writeOutput(const string& filename, int v[N][M], int n, int m) {
    if (!FileManager::writeFile(filename, &v[0][0], n, m)) {
        cerr << "Error writing " << filename << endl;
        return false;
    }
    return true;
}

//compares the computed matrix with the matrix from the file
bool isResultOk(const string& filename, int v[N][M], int n, int m) {
    static int expected[N][M];   // static storage, not on the stack

    int rows, cols;
    if (!FileManager::readDimensions(filename, rows, cols)) {
        cerr << "Error opening " << filename << endl;
        return false;
    }
    if (rows != n || cols != m) {
        cerr << filename << " is " << rows << "x" << cols << " but the static array is " << n << "x" << m << endl;
        return false;
    }
    if (!FileManager::readFile(filename, &expected[0][0], n, m)) {
        cerr << "Error reading " << filename << endl;
        return false;
    }

    if (!equal(&v[0][0], &v[0][0] + n * m, &expected[0][0])) {
        cerr << "Error: the computed result is different from " << filename << endl;
        return false;
    }
    return true;
}
