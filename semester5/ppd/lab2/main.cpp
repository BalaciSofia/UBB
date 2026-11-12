#include <iostream>
#include <thread>
#include <mutex>
#include <numeric>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;

void initializeDynamic(double* X, int n) {
    for (int i = 0; i < n; ++i) {
        X[i] = i;
    }
}

void multiplyDynamic(const double* A, const double* B, double* C, const int start, const int end) {
    for (int i = start; i < end; ++i) {
        C[i] = A[i] * B[i];
    }
}

void multiplyCyclicDynamic(const double* A, const double* B, double* C, int id, int n, int step) {
    for (int i = id; i < n; i += step) {
        C[i] = A[i] * B[i];
    }
}

void sumDynamic(const double* C, int n, double& result) {
    result = 0.0;
    for (int i = 0; i < n; ++i) {
        result += C[i];
    }
}

void ParallelMultiplyDynamic(const double *A, const double *B, double *C,int n, int numThreads) {
    thread threads[numThreads];
    int sliceSize = n / numThreads;
    int modulo = n % numThreads;
    int start = 0;
    for (int i = 0; i < numThreads; ++i) {
        int end = start + sliceSize + (i < modulo ? 1 : 0);
        threads[i] = thread(multiplyDynamic, A, B, C, start, end);
        start = end;
    }
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }
}

void ParallelMultiplyCyclicDynamic(const double *A, const double *B, double *C,int n, int numThreads) {
    thread threads[numThreads];
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = thread(multiplyCyclicDynamic, A, B, C, i, n, numThreads);
    }
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }
}

bool areEqual(const double *A, const double *B, int n) {
    for (int i = 0; i < n; ++i) {
        if (A[i] != B[i]) {
            return false;
        }
    }
    return true;
}

//---------
void sequential (const double* A, const double* B, double* C, int n, double& result) {
    multiplyDynamic(A, B, C, 0, n);
    sumDynamic(C, n, result);
}


void dotProduct(const double* A, const double* B, double* C, int start, int end, double& res) {
    multiplyDynamic(A, B, C, start, end);
    sumDynamic(C + start, end - start, res);
}

void parallel(const double* A, const double* B, double* C, int n, int numThreads, double& result) {
    vector<thread> threads;
    mutex m;
    result = 0.0;
    int sliceSize = n / numThreads;
    int modulo = n % numThreads;
    int start = 0;
    for (int i = 0; i < numThreads; ++i) {
        int end = start + sliceSize + (i < modulo ? 1 : 0);
        threads.emplace_back([=, &result, &m] {
            double partial;
            dotProduct(A, B, C, start, end, partial);
            m.lock();
            result += partial;
            m.unlock();
        });
        start = end;
    }
    for (auto& t : threads) {
        t.join();
    }
}
//---

int main() {
    int n = 10000000;
    int p = 5; //number of threads

    double *A2 = new double[n];
    double *B2 = new double[n];
    double *C2 = new double[n];
    double *D2 = new double[n];
    double *E2 = new double[n];
    initializeDynamic(A2, n);
    initializeDynamic(B2, n);

    auto start2 = chrono::high_resolution_clock::now();
    multiplyDynamic(A2, B2, C2, 0, n);
    auto end2 = chrono::high_resolution_clock::now();

    auto start2_parallel = chrono::high_resolution_clock::now();
    ParallelMultiplyDynamic(A2, B2, D2, n, p);
    auto end2_parallel = chrono::high_resolution_clock::now();

    auto start2_cyclic_parallel = chrono::high_resolution_clock::now();
    ParallelMultiplyCyclicDynamic(A2, B2, E2, n, p);
    auto end2_cyclic_parallel = chrono::high_resolution_clock::now();

    double dotSeq = 0.0, dotPar = 0.0;
    auto startDotSeq = chrono::high_resolution_clock::now();
    sequential(A2, B2, C2, n, dotSeq);
    auto endDotSeq = chrono::high_resolution_clock::now();

    auto startDotPar = chrono::high_resolution_clock::now();
    parallel(A2, B2, D2, n, p, dotPar);
    auto endDotPar = chrono::high_resolution_clock::now();

    cout<< "Dynamic array multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() << " nanoseconds" << endl;
    cout << "Dynamic array parallel multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end2_parallel - start2_parallel).count() << " nanoseconds" << endl;
    cout << "Dynamic array cyclic parallel multiplication time: " << chrono::duration_cast<chrono::nanoseconds>(end2_cyclic_parallel - start2_cyclic_parallel).count() << " nanoseconds" << endl;
    cout << "Are the results of dynamic array multiplication and parallel multiplication equal? " << (areEqual(C2, D2, n) ? "Yes" : "No") << endl;
    cout << "Are the results of dynamic array multiplication and cyclic parallel multiplication equal? " << (areEqual(C2, E2, n) ? "Yes" : "No") << endl;

    cout << "Dynamic array sequential dot product time: " << chrono::duration_cast<chrono::nanoseconds>(endDotSeq - startDotSeq).count() << " nanoseconds" << endl;
    cout << "Dynamic array parallel dot product time: " << chrono::duration_cast<chrono::nanoseconds>(endDotPar - startDotPar).count() << " nanoseconds" << endl;

    cout << "Sequential dot product = " << dotSeq << ", parallel dot product = " << dotPar << endl;

    //thread t1(f0,1); f0 the function and 1 is the param of the f0 function
    //
    // auto id = this_thread::get_id();
    //
    // cout<< "Thread ID: " << id << endl;
    //
    //mutex m
    //thread t(f,param,&m)
    //m.lock();
    //m.unlock();
    //
    //this_thread::sleep_for(chrono::seconds(1));
    // auto main_thread_id = this_thread::get_id();
    // cout <<"Main thread id: " << main_thread_id << endl;

    delete[] A2;
    delete[] B2;
    delete[] C2;
    delete[] D2;
    delete[] E2;
    return 0;
}
