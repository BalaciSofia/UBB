#pragma once

#include <iostream>
#include "../common/RandomNumberGenerator.cpp"
#include "../common/FileManager.cpp"
#include "Convolution.cpp"
#include "InputOutput.cpp"
using namespace std;

void generateAndWriteMatrices(int n, int m, int k) {
    RandomNumberGenerator rng;

    //generate and write matrix F
    int* f = new int[n * m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[i * m + j] = rng.nextInt(1, 100);
        }
    }
    if (!FileManager::writeFile(MATRIX_F_FILE, f, n, m)) {
        cerr << "Error writing integer matrix to file" << endl;
    }

    int* c = new int[k * k];
    //generate and write convolution matrix
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            c[i * k + j] = rng.nextInt(1, 100);
        }
    }
    if (!FileManager::writeFile(CONVOLUTION_FILE, c, k, k)) {
        cerr << "Error writing convolution matrix to file" << endl;
    }

    int* v = new int[n * m];
    //compute and write expected result matrix
    applyConvolutionSequentially(f, c, v, n, m, k);
    if (!FileManager::writeFile(EXPECTED_FILE, v, n, m)) {
        cerr << "Error writing expected result matrix to file" << endl;
    }

    delete[] f;
    delete[] c;
    delete[] v;
}
