#include <chrono>
#include <iostream>
#include <string>
#include "Convolution.cpp"
#include "InputOutput.cpp"
#include "GenerateAndWriteMatrices.cpp"
using namespace std;

int main(int argc, char* argv[]) {
    static int fMatrix[N][M], convMatrix[K][K], vMatrix[N][M];

    //to generate the input files
    int rows, cols, kernelSize;
    if (argc > 1 && string(argv[1]) == "gen") {
        if (argc != 5) {
            cout << "Usage: gen <rows> <cols> <k>" << endl;
            return 0;
        }
        rows = stoi(argv[2]);
        cols = stoi(argv[3]);
        kernelSize = stoi(argv[4]);
        if (rows <= 0 || cols <= 0 || kernelSize <= 0 || kernelSize % 2 == 0) {
            cout << "rows and cols must be positive, k must be a positive odd number" << endl;
            return 0;
        }
        if (rows != N || cols != M || kernelSize != K) {
            cout << "The sizes are fixed at compile time, use: gen " << N << " " << M << " " << K << endl;
            return 0;
        }
        generateAndWriteMatrices(fMatrix, convMatrix, vMatrix, N, M, K);
        cout << "Generated matrices and convolution matrix." << endl;
        return 0;
    }

    //number of threads
    int p = 4;
    if (argc > 1) {
        p = stoi(argv[1]);
        if (p <= 0) {
            cerr << "The number of threads must be positive" << endl;
            return 1;
        }
    }

    //variant of the algorithm to use: seq, rows or cols
    string variant = "";
    if (argc > 2) {
        variant = argv[2];
        if (variant != "seq" && variant != "rows" && variant != "cols") {
            cerr << "The second argument must be seq, rows or cols" << endl;
            return 1;
        }
    }

    // read the input files
    if (!readMatrixF(fMatrix, N, M) || !readConvolutionMatrix(convMatrix, K)) {
        return 1;
    }

    //time the selected variant
    auto start = chrono::high_resolution_clock::now();
    if (variant == "seq") {
        applyConvolutionSequentially(fMatrix, convMatrix, vMatrix, N, M, K);
    } else if (variant == "rows") {
        applyConvolutionParallelRows(fMatrix, convMatrix, vMatrix, N, M, K, p);
    } else if (variant == "cols") {
        applyConvolutionParallelCols(fMatrix, convMatrix, vMatrix, N, M, K, p);
    } else {
        applyConvolutionSequentially(fMatrix, convMatrix, vMatrix, N, M, K);
        //applyConvolutionParallelRows(fMatrix, convMatrix, vMatrix, N, M, K, p);
        //applyConvolutionParallelCols(fMatrix, convMatrix, vMatrix, N, M, K, p);
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> time = end - start;
    cout << time.count() << endl;

    //check if the result is correct
    bool ok = isResultOk(EXPECTED_FILE, vMatrix, N, M);

    //write the result to the output file
    bool written = writeOutput(OUTPUT_FILE, vMatrix, N, M);

    return (ok && written) ? 0 : 1;
}
