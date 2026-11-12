#pragma once

#include <iostream>
#include "RandomNumberGenerator.cpp"
#include "FileManager.cpp"
#include "Convolution.cpp"
#include "InputOutput.cpp"
using namespace std;

void generateAndWriteMatrices(int n, int m) {
    const int k = 3;
    RandomNumberGenerator rng;

    //generate matrix F
    int* f = new int[n * m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[i * m + j] = rng.nextInt(1, 100);
        }
    }

    //generate convolution matrix
    int* c = new int[k * k];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            c[i * k + j] = rng.nextInt(1, 100);
        }
    }

    //write both of them in the data file (the convolution matrix is appended after an empty line)
    if (!FileManager::writeFile(DATA_FILE, f, n, m) || !FileManager::writeFile(DATA_FILE, c, k, k, true)) {
        cerr << "Error writing " << DATA_FILE << endl;
    }

    //compute and write expected result matrix
    applyConvolutionSequentially(f, c, n, m);
    if (!FileManager::writeFile(EXPECTED_FILE, f, n, m)) {
        cerr << "Error writing expected result matrix to file" << endl;
    }

    delete[] f;
    delete[] c;
}
