#pragma once

#include <thread>
#include <vector>
using namespace std;

// static allocation: the sizes are fixed at compile time (set them here or with -DMATRIX_N=... -DMATRIX_M=... -DMATRIX_K=...)
#ifndef MATRIX_N
#define MATRIX_N 1000
#endif
#ifndef MATRIX_M
#define MATRIX_M 1000
#endif
#ifndef MATRIX_K
#define MATRIX_K 3
#endif

const int N = MATRIX_N;
const int M = MATRIX_M;
const int K = MATRIX_K;

void applyConvolutionSequentially(int f[N][M], int c[K][K], int v[N][M], int n, int m, int k) {
    int r = k / 2; //radius of the convolution matrix

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int sum = 0;
            // sum for the element (i, j)
            for (int a = 0; a < k; a++) {
                for (int b = 0; b < k; b++) {
                    int fi = i + a - r;
                    int fj = j + b - r;

                    if (fi < 0) fi = 0;
                    if (fi >= n) fi = n - 1;
                    if (fj < 0) fj = 0;
                    if (fj >= m) fj = m - 1;

                    sum += f[fi][fj] * c[a][b];
                }
            }
            v[i][j] = sum;
        }
    }
}


void computeRows(int f[N][M], int c[K][K], int v[N][M], int n, int m, int k, int startRow, int endRow) {
    int r = k / 2;

    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < m; j++) {
            int sum = 0;
            for (int a = 0; a < k; a++) {
                for (int b = 0; b < k; b++) {
                    int fi = i + a - r;
                    int fj = j + b - r;

                    if (fi < 0) fi = 0;
                    if (fi >= n) fi = n - 1;
                    if (fj < 0) fj = 0;
                    if (fj >= m) fj = m - 1;

                    sum += f[fi][fj] * c[a][b];
                }
            }
            v[i][j] = sum;
        }
    }
}

void computeCols(int f[N][M], int c[K][K], int v[N][M], int n, int m, int k, int startCol, int endCol) {
    int r = k / 2;

    for (int j = startCol; j < endCol; j++) {
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int a = 0; a < k; a++) {
                for (int b = 0; b < k; b++) {
                    int fi = i + a - r;
                    int fj = j + b - r;

                    if (fi < 0) fi = 0;
                    if (fi >= n) fi = n - 1;
                    if (fj < 0) fj = 0;
                    if (fj >= m) fj = m - 1;

                    sum += f[fi][fj] * c[a][b];
                }
            }
            v[i][j] = sum;
        }
    }
}

//apply convolution with threads ---- block of rows
void applyConvolutionParallelRows(int f[N][M], int c[K][K], int v[N][M], int n, int m, int k, int p) {
    //if there are more threads than rows, we can only use n threads
    if (p > n) {
        p = n;
    }

    vector<thread> threads;
    int base = n / p; //base number of rows per thread
    int rem = n % p; //remaining rows to distribute among the first 'rem' threads
    int start = 0;

    for (int t = 0; t < p; t++) {
        int end = start + base + (t < rem ? 1 : 0);
        threads.emplace_back(computeRows, f, c, v, n, m, k, start, end);
        start = end;
    }

    for (thread& th : threads) {
        th.join();
    }
}

//apply convolution with threads ---- a block of columns
void applyConvolutionParallelCols(int f[N][M], int c[K][K], int v[N][M], int n, int m, int k, int p) {
    if (p > m) {
        p = m;
    }

    vector<thread> threads;
    int base = m / p;
    int rem = m % p;
    int start = 0;

    for (int t = 0; t < p; t++) {
        int end = start + base + (t < rem ? 1 : 0);
        threads.emplace_back(computeCols, f, c, v, n, m, k, start, end);
        start = end;
    }

    for (thread& th : threads) {
        th.join();
    }
}
