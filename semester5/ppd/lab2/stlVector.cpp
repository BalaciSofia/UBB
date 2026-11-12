#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

void initializeStlVector(vector<double>& X) {
    for (size_t i = 0; i < X.size(); ++i) {
        X[i] = static_cast<double>(i);
    }
}

void multiplyStlVector(const vector<double>& A, const vector<double>& B, vector<double>& C, int start, int end) {
    for (int i = start; i < end; ++i) {
        C[i] = A[i] * B[i];
    }
}

void multiplyCyclicStlVector(const vector<double>& A, const vector<double>& B, vector<double>& C, int id, int n, int step) {
    for (int i = id; i < n; i += step) {
        C[i] = A[i] * B[i];
    }
}

void ParallelMultiplyStlVector(const vector<double>& A, const vector<double>& B, vector<double>& C, int n, int numThreads) {
    vector<thread> threads;
    int sliceSize = n / numThreads;
    int modulo = n % numThreads;
    int start = 0;
    for (int i = 0; i < numThreads; ++i) {
        int end = start + sliceSize + (i < modulo ? 1 : 0);
        threads.emplace_back(multiplyStlVector, cref(A), cref(B), ref(C), start, end);
        start = end;
    }
    for (auto& t : threads) t.join();
}

void ParallelMultiplyCyclicStlVector(const vector<double>& A, const vector<double>& B, vector<double>& C, int n, int numThreads) {
    vector<thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(multiplyCyclicStlVector, cref(A), cref(B), ref(C), i, n, numThreads);
    }
    for (auto& t : threads) t.join();
}

int main() {
    int n = 10000000;
    int p = 5; // number of threads

    vector<double> A3(n), B3(n), C3(n), D3(n), E3(n);
    initializeStlVector(A3);
    initializeStlVector(B3);

    auto start3 = chrono::high_resolution_clock::now();
    multiplyStlVector(A3, B3, C3, 0, n);
    auto end3 = chrono::high_resolution_clock::now();

    auto start3_parallel = chrono::high_resolution_clock::now();
    ParallelMultiplyStlVector(A3, B3, D3, n, p);
    auto end3_parallel = chrono::high_resolution_clock::now();

    auto start3_cyclic = chrono::high_resolution_clock::now();
    ParallelMultiplyCyclicStlVector(A3, B3, E3, n, p);
    auto end3_cyclic = chrono::high_resolution_clock::now();

    cout << "STL vector multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count() << " nanoseconds" << endl;
    cout << "STL vector parallel multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end3_parallel - start3_parallel).count() << " nanoseconds" << endl;
    cout << "STL vector cyclic parallel multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end3_cyclic - start3_cyclic).count() << " nanoseconds" << endl;
    cout << "Are the results of vector multiplication and parallel multiplication equal? " << (C3 == D3 ? "Yes" : "No") << endl;
    cout << "Are the results of vector multiplication and cyclic parallel multiplication equal? " << (C3 == E3 ? "Yes" : "No") << endl;
    return 0;
}
