#include <iostream>
#include <fstream>
#include <chrono>
#include "number_io.h"
using namespace std;

pair<int, int*> addNumbers(const int* number1, const int* number2, int n, int m) {
    int maxSize = max(n, m);
    int* result = new int[maxSize + 1];
    int carry = 0;
    for (int i = 0; i < maxSize; i++) {
        int digit1 = (i < n) ? number1[i] : 0;
        int digit2 = (i < m) ? number2[i] : 0;
        int sum = digit1 + digit2 + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    int size = maxSize;
    if (carry > 0) {
        result[maxSize] = carry;
        size = maxSize + 1;
    }
    return {size, result};
}

int main(int argc, char** argv) {
    auto start = chrono::high_resolution_clock::now();

    ifstream file1 = openFile("Number1.txt");
    ifstream file2 = openFile("Number2.txt");
    int n = readDigitCount(file1);
    int m = readDigitCount(file2);

    int* number1 = new int[n];
    int* number2 = new int[m];
    if (readDigits(file1, number1, n) != n || readDigits(file2, number2, m) != m) {
        cerr << "A file contains fewer digits than declared" << endl;
        return 1;
    }

    pair<int, int*> res = addNumbers(number1, number2, n, m);
    int size = res.first;
    int* result = res.second;
    auto end = chrono::high_resolution_clock::now();


    ofstream out("ExpectedResult.txt");
    writeDigits(out, result, size);
    out.close();

    double ms = chrono::duration<double, milli>(end - start).count();
    cout << "Time: " << ms << " ms" << endl;

    delete[] number1;
    delete[] number2;
    delete[] result;
    return 0;
}
