#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>

class RandomNumberGenerator {
public:
    RandomNumberGenerator();
    int nextInt(int low, int high);
    double nextDouble(double low, double high);
private:
    std::mt19937 engine;
};

#endif //RANDOMNUMBERGENERATOR_H
