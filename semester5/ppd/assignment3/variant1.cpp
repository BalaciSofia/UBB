#include <iostream>
#include <fstream>
#include <algorithm>
#include <mpi.h>
#include "number_io.h"
using namespace std;

int chunkSize(int N, int workers, int id) {
    return N / workers + ((id - 1) < N % workers ? 1 : 0);
}

void master(int p) {
    double start = MPI_Wtime();

    ifstream file1 = openFile("Number1.txt");
    ifstream file2 = openFile("Number2.txt");
    int n = readDigitCount(file1);
    int m = readDigitCount(file2);
    int N = max(n, m);
    int workers = p - 1;

    int maxChunk = N / workers + 1;
    int* digits1 = new int[maxChunk];
    int* digits2 = new int[maxChunk];

    for (int id_proces_curent = 1; id_proces_curent <= workers; id_proces_curent++) {
        int k = chunkSize(N, workers, id_proces_curent);

        int read1 = readDigits(file1, digits1, k);
        int read2 = readDigits(file2, digits2, k);
        fill(digits1 + read1, digits1 + k, 0);
        fill(digits2 + read2, digits2 + k, 0);

        MPI_Send(digits1, k, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD);
        MPI_Send(digits2, k, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD);
    }

    ofstream out("Number3.txt");
    int* result = new int[N + 1];
    int size = 0;
    for (int id = 1; id <= workers; id++) {
        MPI_Status status;
        int count;
        MPI_Recv(result + size, N + 1 - size, MPI_INT, id, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        writeDigits(out, result + size, count);
        size += count;
    }
    out.close();

    double end = MPI_Wtime();
    cout << "Time: " << (end - start) * 1000 << " ms" << endl;
    checkResult(result, size);

    delete[] digits1;
    delete[] digits2;
    delete[] result;
}

void worker(int id, int p) {
    MPI_Status status;
    int k;

    MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &k);
    int* digits1 = new int[k];
    int* digits2 = new int[k];
    int* result  = new int[k + 1];
    MPI_Recv(digits1, k, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(digits2, k, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int carry = 0;
    if (id > 1) {
        MPI_Recv(&carry, 1, MPI_INT, id - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < k; i++) {
        int sum = digits1[i] + digits2[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }

    int resultSize = k;
    if (id < p - 1) {
        MPI_Send(&carry, 1, MPI_INT, id + 1, 0, MPI_COMM_WORLD);
    } else if (carry > 0) {
        result[k] = carry;
        resultSize = k + 1;
    }

    MPI_Send(result, resultSize, MPI_INT, 0, 0, MPI_COMM_WORLD);

    delete[] digits1;
    delete[] digits2;
    delete[] result;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, p;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (rank == 0) {
        master(p);
    } else {
        worker(rank, p);
    }

    MPI_Finalize();
    return 0;
}
