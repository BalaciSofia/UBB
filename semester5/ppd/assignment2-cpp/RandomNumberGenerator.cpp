#pragma once

#include <chrono>
#include <random>

class RandomNumberGenerator {
private:
    std::mt19937 engine;

public:
    RandomNumberGenerator() {
        std::random_device rd;
        auto time = static_cast<unsigned>(
            std::chrono::steady_clock::now().time_since_epoch().count());
        engine.seed(rd() ^ time);
    }

    // random integer in [low, high], both included
    int nextInt(int low, int high) {
        std::uniform_int_distribution<int> dist(low, high);
        return dist(engine);
    }
};
