#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <n> <filename>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        cerr << "n must be a positive integer" << endl;
        return 1;
    }
    string filename = argv[2];

    ofstream out(filename);
    if (!out) {
        cerr << "Could not open " << filename << endl;
        return 1;
    }

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> digit(0, 9);
    uniform_int_distribution<int> nonZero(1, 9);

    out << n << '\n';
    for (int i = 0; i < n - 1; i++) {
        out << (char)('0' + digit(gen));
    }
    out << (char)('0' + nonZero(gen));
    out << '\n';

    return 0;
}
