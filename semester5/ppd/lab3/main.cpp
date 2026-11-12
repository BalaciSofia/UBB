#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[] )
{
int rank, size;
MPI_Init( &argc, &argv );

MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

if ( rank == 0 ){
    int N = 10;
    int* vectorA = new int[N];
    int* vectorB = new int[N];
    int* vectorResult = new int[N];

    for( int i = 0; i < N ; i++ ){
        vectorA[i]=i;
        vectorB[i]=i;
    }

    int chunlkSize = N/ (size-1);
    int r = N%(size-1);

    int start = 0;

    for(int i = 1; i < size; i++){
        int length = (i <= r ) ? chunlkSize + 1 : chunlkSize;
        MPI_Send(&N,1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(vectorA + start, length, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(vectorB + start, length, MPI_INT, i, 0, MPI_COMM_WORLD);
        start += length;
    }

    int startIdx = 0;
    for (int i = 1; i < size; i++){
        MPI_Status status;
        MPI_Recv(vectorResult + startIdx, chunlkSize+1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        int length;
        MPI_Get_count(&status, MPI_INT, &length);
        startIdx += length;
    }

    cout <<"Result vector with processes: ";
    for (int i = 0; i < N; i++){
        cout<<vectorResult[i]<<" ";
    }
    cout<<"\n";

    cout<<"Result vector without processes: ";
    for (int i = 0; i < N; i++){
        cout<<vectorA[i] * vectorB[i]<<" ";
    }
    cout<<"\n";

    delete[] vectorA;
    delete[] vectorB;
    delete[] vectorResult;
}
else {
    int N;
    MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int chunkSize = N/(size-1);
    int r = N%(size-1);
    int length = (rank <= r) ? chunkSize + 1 : chunkSize;

    int* vectorA = new int[length];
    int* vectorB = new int[length];
    int* vectorResult = new int[length];

    MPI_Recv(vectorA, length, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(vectorB, length, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    for(int i = 0; i < length; i++){
        vectorResult[i] = vectorA[i] * vectorB[i];
    }

    MPI_Send(vectorResult, length, MPI_INT, 0, 0, MPI_COMM_WORLD);

    delete[] vectorA;
    delete[] vectorB;
    delete[] vectorResult;
}

MPI_Finalize();

return 0;
}
