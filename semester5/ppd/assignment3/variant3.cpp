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

    int* digits1 = new int[N];
    int* digits2 = new int[N];
    int* result  = new int[N + 1];
    int* sizes   = new int[p];
    int* offset  = new int[p];

    MPI_Request* sendReqs = new MPI_Request[3 * workers];
    MPI_Request* recvReqs = new MPI_Request[p];

    int pos = 0;
    for (int id = 1; id <= workers; id++) {
        sizes[id] = chunkSize(N, workers, id);
        offset[id] = pos;
        pos += sizes[id];
    }

    for (int id = 1; id <= workers; id++) {
        int count = sizes[id] + (id == workers ? 1 : 0);
        MPI_Irecv(result + offset[id], count, MPI_INT, id, 0, MPI_COMM_WORLD, &recvReqs[id]);
    }

    for (int id_proces_curent = 1; id_proces_curent <= workers; id_proces_curent++) {
        int k = sizes[id_proces_curent];
        int* chunk1 = digits1 + offset[id_proces_curent];
        int* chunk2 = digits2 + offset[id_proces_curent];

        int read1 = readDigits(file1, chunk1, k);
        int read2 = readDigits(file2, chunk2, k);
        fill(chunk1 + read1, chunk1 + k, 0);
        fill(chunk2 + read2, chunk2 + k, 0);

        int r = 3 * (id_proces_curent - 1);
        MPI_Isend(&sizes[id_proces_curent], 1, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD, &sendReqs[r]);
        MPI_Isend(chunk1, k, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD, &sendReqs[r + 1]);
        MPI_Isend(chunk2, k, MPI_INT, id_proces_curent, 0, MPI_COMM_WORLD, &sendReqs[r + 2]);
    }

    ofstream out("Number3.txt");
    int size = 0;
    for (int id = 1; id <= workers; id++) {
        MPI_Status status;
        int count;
        MPI_Wait(&recvReqs[id], &status);
        MPI_Get_count(&status, MPI_INT, &count);
        writeDigits(out, result + offset[id], count);
        size += count;
    }
    out.close();

    MPI_Waitall(3 * workers, sendReqs, MPI_STATUSES_IGNORE);

    double end = MPI_Wtime();
    cout << "Time: " << (end - start) * 1000 << " ms" << endl;
    checkResult(result, size);

    delete[] digits1;
    delete[] digits2;
    delete[] result;
    delete[] sizes;
    delete[] offset;
    delete[] sendReqs;
    delete[] recvReqs;
}

void worker(int id, int p) {
    int carry = 0;
    MPI_Request carryReq = MPI_REQUEST_NULL;
    if (id > 1) {
        MPI_Irecv(&carry, 1, MPI_INT, id - 1, 0, MPI_COMM_WORLD, &carryReq);
    }

    int k;
    MPI_Request req;
    MPI_Irecv(&k, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);
    MPI_Wait(&req, MPI_STATUS_IGNORE);

    int* digits1 = new int[k];
    int* digits2 = new int[k];
    int* result  = new int[k + 1];
    MPI_Request digitReqs[2];
    MPI_Irecv(digits1, k, MPI_INT, 0, 0, MPI_COMM_WORLD, &digitReqs[0]);
    MPI_Irecv(digits2, k, MPI_INT, 0, 0, MPI_COMM_WORLD, &digitReqs[1]);
    MPI_Waitall(2, digitReqs, MPI_STATUSES_IGNORE);
    MPI_Wait(&carryReq, MPI_STATUS_IGNORE);

    for (int i = 0; i < k; i++) {
        int sum = digits1[i] + digits2[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }

    MPI_Request outReqs[2];
    int nOut = 0;
    int resultSize = k;
    if (id < p - 1) {
        MPI_Isend(&carry, 1, MPI_INT, id + 1, 0, MPI_COMM_WORLD, &outReqs[nOut++]);
    } else if (carry > 0) {
        result[k] = carry;
        resultSize = k + 1;
    }
    MPI_Isend(result, resultSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &outReqs[nOut++]);
    MPI_Waitall(nOut, outReqs, MPI_STATUSES_IGNORE);

    delete[] digits1;
    delete[] digits2;
    delete[] result;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, p;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (p < 2) {
        if (rank == 0) cerr << "Need at least 2 processes" << endl;
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        master(p);
    } else {
        worker(rank, p);
    }

    MPI_Finalize();
    return 0;
}
