#include <chrono>
#include <iostream>
#include <string>
#include "Convolution.cpp"
#include "InputOutput.cpp"
#include "GenerateAndWriteMatrices.cpp"
using namespace std;

int main(int argc, char* argv[]) {
    //to generate the input file (the convolution matrix is always 3x3)
    int rows, cols;
    if (argc > 1 && string(argv[1]) == "gen") {
        if (argc != 4) {
            cout << "Usage: gen <rows> <cols>" << endl;
            return 0;
        }
        rows = stoi(argv[2]);
        cols = stoi(argv[3]);
        if (rows <= 0 || cols <= 0) {
            cout << "rows and cols must be positive" << endl;
            return 0;
        }
        generateAndWriteMatrices(rows, cols);
        cout << "Generated " << DATA_FILE << " and " << EXPECTED_FILE << "." << endl;
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

    //variant of the algorithm to use: seq or rows
    string variant = "";
    if (argc > 2) {
        variant = argv[2];
        if (variant != "seq" && variant != "rows") {
            cerr << "The second argument must be seq or rows" << endl;
            return 1;
        }
    }

    int n, m, k;
    int *fMatrix = nullptr, *convMatrix = nullptr;

    // read the input file
    if (!readData(fMatrix, n, m, convMatrix, k)) {
        delete[] fMatrix;
        delete[] convMatrix;
        return 1;
    }

    //time the selected variant (the result is written in fMatrix)
    auto start = chrono::high_resolution_clock::now();
    if (variant == "seq") {
        applyConvolutionSequentially(fMatrix, convMatrix, n, m);
    } else if (variant == "rows") {
        applyConvolutionParallelRows(fMatrix, convMatrix, n, m, p);
    } else {
        applyConvolutionSequentially(fMatrix, convMatrix, n, m);
        //applyConvolutionParallelRows(fMatrix, convMatrix, n, m, p);
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> time = end - start;
    cout << time.count() << endl;

    //check if the result is correct
    bool ok = isResultOk(EXPECTED_FILE, fMatrix, n, m);

    //write the result to the output file
    bool written = writeOutput(OUTPUT_FILE, fMatrix, n, m);

    delete[] fMatrix;
    delete[] convMatrix;

    return (ok && written) ? 0 : 1;
}
