#pragma once

#include <iostream>
#include "../common/RandomNumberGenerator.cpp"
#include "../common/FileManager.cpp"
#include "Convolution.cpp"
#include "InputOutput.cpp"
using namespace std;

void generateAndWriteMatrices(int f[N][M], int c[K][K], int v[N][M], int n, int m, int k) {
    RandomNumberGenerator rng;

    //generate and write matrix F
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[i][j] = rng.nextInt(1, 100);
        }
    }
    if (!FileManager::writeFile(MATRIX_F_FILE, &f[0][0], n, m)) {
        cerr << "Error writing integer matrix to file" << endl;
    }

    //generate and write convolution matrix
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            c[i][j] = rng.nextInt(1, 100);
        }
    }
    if (!FileManager::writeFile(CONVOLUTION_FILE, &c[0][0], k, k)) {
        cerr << "Error writing convolution matrix to file" << endl;
    }

    //compute and write expected result matrix
    applyConvolutionSequentially(f, c, v, n, m, k);
    if (!FileManager::writeFile(EXPECTED_FILE, &v[0][0], n, m)) {
        cerr << "Error writing expected result matrix to file" << endl;
    }
}
