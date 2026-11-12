#pragma once

#include <algorithm>
#include <barrier>
#include <functional>
#include <thread>
#include <vector>
using namespace std;

//computes the new values of one row
void computeRow(const int* up, const int* mid, const int* down, const int* c, int* out, int m) {
    for (int j = 0; j < m; j++) {
        int left = j > 0 ? j - 1 : 0;
        int right = j < m - 1 ? j + 1 : m - 1;

        out[j] = up[left] * c[0] + up[j] * c[1] + up[right] * c[2]
               + mid[left] * c[3] + mid[j] * c[4] + mid[right] * c[5]
               + down[left] * c[6] + down[j] * c[7] + down[right] * c[8];
    }
}

//the result is written in f, only 2 temporary vectors of size m are used
void applyConvolutionSequentially(int* f, int* c, int n, int m) {
    int* prev = new int[m]; //original values of row above
    int* cur = new int[m];  //original values of current row

    //row -1 is equal to row 0
    copy(f, f + m, prev);

    for (int i = 0; i < n; i++) {
        copy(f + i * m, f + (i + 1) * m, cur);
        //row i + 1 is not modified yet
        int* next = (i + 1 < n) ? f + (i + 1) * m : cur;

        computeRow(prev, cur, next, c, f + i * m, m);
        swap(prev, cur);
    }

    delete[] prev;
    delete[] cur;
}

//variant 1b: copy the neighbour rows, barrier, then update the rows of the thread
void computeRows(int* f, int* c, int n, int m, int startRow, int endRow, barrier<>& syncBarrier) {
    int* prev = new int[m];   //original values of row above
    int* cur = new int[m];    //original values of row current (to be updated)
    int* bottom = new int[m]; //original values of the row below

    int above = startRow > 0 ? startRow - 1 : 0;
    int below = endRow < n ? endRow : n - 1;
    copy(f + above * m, f + (above + 1) * m, prev);
    copy(f + below * m, f + (below + 1) * m, bottom);

    //wait until all threads copied their boundaries
    syncBarrier.arrive_and_wait();

    //update the rows, using the copied boundaries where needed
    for (int i = startRow; i < endRow; i++) {
        copy(f + i * m, f + (i + 1) * m, cur);
        int* next = (i + 1 < endRow) ? f + (i + 1) * m : bottom;

        computeRow(prev, cur, next, c, f + i * m, m);
        swap(prev, cur);
    }

    delete[] prev;
    delete[] cur;
    delete[] bottom;
}

//apply convolution with threads ---- block of rows
void applyConvolutionParallelRows(int* f, int* c, int n, int m, int p) {
    //if there are more threads than rows, we can only use n threads
    if (p > n) {
        p = n;
    }

    barrier<> syncBarrier(p);
    vector<thread> threads;
    int base = n / p; //base number of rows per thread
    int rem = n % p; //remaining rows to distribute among the first 'rem' threads
    int start = 0;

    for (int t = 0; t < p; t++) {
        int end = start + base + (t < rem ? 1 : 0);
        threads.emplace_back(computeRows, f, c, n, m, start, end, ref(syncBarrier));
        start = end;
    }

    for (thread& th : threads) {
        th.join();
    }
}
