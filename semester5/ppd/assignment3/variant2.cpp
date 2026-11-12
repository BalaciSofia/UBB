#include <iostream>
#include <fstream>
#include <algorithm>
#include <mpi.h>
#include "number_io.h"
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, p;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    double start = MPI_Wtime();

    int n = 0, m = 0, N = 0, chunk = 0;
    int* number1 = nullptr;
    int* number2 = nullptr;
    int* result  = nullptr;

    if (rank == 0) {
        ifstream file1 = openFile("Number1.txt");
        ifstream file2 = openFile("Number2.txt");
        n = readDigitCount(file1);
        m = readDigitCount(file2);

        int maxLen = max(n, m);
        chunk = (maxLen + p - 1) / p;
        N = chunk * p;

        number1 = new int[N]();
        number2 = new int[N]();
        result  = new int[N];
        readDigits(file1, number1, n);
        readDigits(file2, number2, m);
    }

    MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int* local1 = new int[chunk];
    int* local2 = new int[chunk];
    int* localResult = new int[chunk];
    MPI_Scatter(number1, chunk, MPI_INT, local1, chunk, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(number2, chunk, MPI_INT, local2, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    int carry = 0;
    if (rank > 0) {
        MPI_Recv(&carry, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    for (int i = 0; i < chunk; i++) {
        int sum = local1[i] + local2[i] + carry;
        localResult[i] = sum % 10;
        carry = sum / 10;
    }
    if (rank < p - 1) {
        MPI_Send(&carry, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Gather(localResult, chunk, MPI_INT, result, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    int finalCarry = carry;
    if (p > 1) {
        if (rank == p - 1) {
            MPI_Send(&carry, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        } else if (rank == 0) {
            MPI_Recv(&finalCarry, 1, MPI_INT, p - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (rank == 0) {
        int size = N;
        if (finalCarry > 0) {
            int* bigger = new int[N + 1];
            copy(result, result + N, bigger);
            bigger[N] = finalCarry;
            delete[] result;
            result = bigger;
            size = N + 1;
        }
        int maxLen = max(n, m);
        while (size > maxLen && result[size - 1] == 0) {
            size--;
        }

        ofstream out("Number3.txt");
        writeDigits(out, result, size);
        out.close();

        double end = MPI_Wtime();
        cout << "Time: " << (end - start) * 1000 << " ms" << endl;
        checkResult(result, size);

        delete[] number1;
        delete[] number2;
        delete[] result;
    }

    delete[] local1;
    delete[] local2;
    delete[] localResult;

    MPI_Finalize();
    return 0;
}
