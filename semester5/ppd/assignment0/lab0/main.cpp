#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "FileManager.h"
#include "RandomNumberGenerator.h"

constexpr int MAX_N = 1000000;
constexpr double MIN_VALUE = 0.0;
constexpr double MAX_VALUE = 1000.0;

std::vector<double> AddVectors(
    const std::vector<double>& vec1,
    const std::vector<double>& vec2
) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument("Size of vectors do not match");
    }
    std::vector<double> result;
    result.reserve(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result.push_back(vec1[i] + vec2[i]);
    }
    return result;
}

void generateFiles() {
    RandomNumberGenerator rng;
    FileManager manager;
    int n = rng.nextInt(1, MAX_N);

    std::vector<double> A, B;
    A.reserve(n);
    B.reserve(n);
    for (int i = 0; i < n; ++i) {
        A.push_back(rng.nextDouble(MIN_VALUE, MAX_VALUE));
        B.push_back(rng.nextDouble(MIN_VALUE, MAX_VALUE));
    }
    manager.writeFile("A.txt", A);
    manager.writeFile("B.txt", B);
    std::cout << "Generated " << n << " numbers in A.txt and B.txt" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "gen") {
        generateFiles();
        return 0;
    }
    FileManager manager;
    std::vector<double> A = manager.readFile("A.txt");
    std::vector<double> B = manager.readFile("B.txt");
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<double> C = AddVectors(A, B);
    auto t2 = std::chrono::high_resolution_clock::now();
    manager.writeFile("C.txt", C);
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count();
    return 0;
}
