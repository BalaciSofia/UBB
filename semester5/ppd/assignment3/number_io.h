#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::ifstream openFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open " << filename << std::endl;
        std::exit(1);
    }
    return file;
}

int readDigitCount(std::ifstream& file) {
    int n;
    if (!(file >> n) || n < 0) {
        std::cerr << "Invalid digit count" << std::endl;
        std::exit(1);
    }
    return n;
}

int readDigits(std::ifstream& file, int* buffer, int k) {
    int count = 0;
    char c;
    while (count < k && file >> c) {
        if (c < '0' || c > '9') {
            std::cerr << "Invalid digit '" << c << "'" << std::endl;
            std::exit(1);
        }
        buffer[count++] = c - '0';
    }
    return count;
}

void writeDigits(std::ofstream& file, const int* digits, int k) {
    for (int i = 0; i < k; i++) {
        file << (char)('0' + digits[i]);
    }
}

bool checkResult(const int* result, int size, const std::string& expectedFile = "ExpectedResult.txt") {
    std::ifstream expected(expectedFile);
    if (!expected) {
        std::cout << "Result: cannot check (missing " << expectedFile << ")" << std::endl;
        return false;
    }

    bool same = true;
    char c;
    for (int i = 0; i < size && same; i++) {
        if (!(expected >> c) || c - '0' != result[i]) {
            same = false;
        }
    }
    if (same && expected >> c) {
        same = false;
    }

    std::cout << "Result: " << (same ? "correct" : "INCORRECT") << std::endl;
    return same;
}
