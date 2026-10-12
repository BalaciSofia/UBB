#include "RandomNumberGenerator.h"

#include <chrono>

RandomNumberGenerator::RandomNumberGenerator() {
    std::random_device rd;
    auto time = static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count());
    engine.seed(rd() ^ time);
}

int RandomNumberGenerator::nextInt(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(engine);
}

double RandomNumberGenerator::nextDouble(double low, double high) {
    std::uniform_real_distribution<double> dist(low, high);
    return dist(engine);
}
