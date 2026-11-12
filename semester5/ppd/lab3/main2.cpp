#include "mpi.h"
#include <iostream>
using namespace std;

int main( int argc, char *argv[] )
{
    int rank, size;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    // int N;
    int N = 10;
    int* vectorA = new int[N];
    int* vectorB = new int[N];
    // int* vectorResult = new int[N/(size-1)];

    if (rank == 0){
        // N=10;
        for( int i = 0; i < N ; i++ ){
            vectorA[i]=i;
            vectorB[i]=i;
        }
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // int chunkSize = N/(size-1);
    int chunkSize = N/size;

    int* localA = new int[chunkSize];
    int* localB = new int[chunkSize];
    // int* localResult = new int[chunkSize];

    MPI_Scatter(vectorA, chunkSize, MPI_INT, localA, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vectorB, chunkSize, MPI_INT, localB, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);

    // for(int i = 0; i < chunkSize; i++){
    //     localResult[i] = localA[i] * localB[i];
    // }
    //
    // MPI_Gather(localResult, chunkSize, MPI_INT, vectorResult, chunkSize , MPI_INT, 0, MPI_COMM_WORLD);

    int localProduct = 0;
    for(int i = 0; i < chunkSize; i++){
        localProduct += localA[i] * localB[i];
    }

    int scalarProduct = 0;
    MPI_Reduce(&localProduct, &scalarProduct, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        // for(int i=chunkSize*size; i<N; i++) {
        //     vectorResult[i] = vectorA[i] * vectorB[i];
        // }
        // cout <<"Result vector with processes: ";
        // for (int i = 0; i < N; i++){
        //     cout<<vectorResult[i]<<" ";
        // }
        // cout<<"\n";
        //
        // cout<<"Result vector without processes: ";
        // for (int i = 0; i < N; i++){
        //     cout<<vectorA[i] * vectorB[i]<<" ";
        // }
        // cout<<"\n";

         for(int i=chunkSize*size; i<N; i++) {
            scalarProduct += vectorA[i] * vectorB[i];
        }
        cout <<"Scalar product with processes: "<<scalarProduct<<"\n";

        int expected = 0;
        for (int i = 0; i < N; i++){
            expected += vectorA[i] * vectorB[i];
        }
        cout<<"Scalar product without processes: "<<expected<<"\n";
    }

    delete[] vectorA;
    delete[] vectorB;
    // delete[] vectorResult;
    delete[] localA;
    delete[] localB;
    // delete[] localResult;

    MPI_Finalize();
}
