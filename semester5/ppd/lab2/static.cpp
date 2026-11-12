#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

const int n = 10000000;
const int p = 5;

static double A1[n], B1[n], C1[n], D1[n], E1[n];

void initializeStatic(double X[], int n) {
    for (int i = 0; i < n; ++i) {
        X[i] = i;
    }
}

void multiplyStatic(const double A[], const double B[], double C[], int start, int end) {
    for (int i = start; i < end; ++i) {
        C[i] = A[i] * B[i];
    }
}

void multiplyCyclicStatic(const double A[], const double B[], double C[], int id, int n, int step) {
    for (int i = id; i < n; i += step) {
        C[i] = A[i] * B[i];
    }
}

void ParallelMultiplyStatic(const double A[], const double B[], double C[], int n, int numThreads) {
    vector<thread> threads;
    int sliceSize = n / numThreads;
    int modulo = n % numThreads;
    int start = 0;
    for (int i = 0; i < numThreads; ++i) {
        int end = start + sliceSize + (i < modulo ? 1 : 0);
        threads.emplace_back(multiplyStatic, A, B, C, start, end);
        start = end;
    }
    for (auto& t : threads) t.join();
}

void ParallelMultiplyCyclicStatic(const double A[], const double B[], double C[], int n, int numThreads) {
    vector<thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(multiplyCyclicStatic, A, B, C, i, n, numThreads);
    }
    for (auto& t : threads) t.join();
}

bool areEqual(const double A[], const double B[], int n) {
    for (int i = 0; i < n; ++i) {
        if (A[i] != B[i]) return false;
    }
    return true;
}

int main() {
    initializeStatic(A1, n);
    initializeStatic(B1, n);

    auto start1 = chrono::high_resolution_clock::now();
    multiplyStatic(A1, B1, C1, 0, n);
    auto end1 = chrono::high_resolution_clock::now();

    auto start1_parallel = chrono::high_resolution_clock::now();
    ParallelMultiplyStatic(A1, B1, D1, n, p);
    auto end1_parallel = chrono::high_resolution_clock::now();

    auto start1_cyclic = chrono::high_resolution_clock::now();
    ParallelMultiplyCyclicStatic(A1, B1, E1, n, p);
    auto end1_cyclic = chrono::high_resolution_clock::now();

    cout << "Static array multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " nanoseconds" << endl;
    cout << "Static array parallel multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end1_parallel - start1_parallel).count() << " nanoseconds" << endl;
    cout << "Static array cyclic parallel multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end1_cyclic - start1_cyclic).count() << " nanoseconds" << endl;
    cout << "Are the results of static array multiplication and parallel multiplication equal? " << (areEqual(C1, D1, n) ? "Yes" : "No") << endl;
    cout << "Are the results of static array multiplication and cyclic parallel multiplication equal? " << (areEqual(C1, E1, n) ? "Yes" : "No") << endl;
    return 0;
}
