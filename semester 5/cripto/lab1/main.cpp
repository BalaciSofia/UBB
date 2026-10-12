#include <algorithm>
#include <chrono>
#include <iostream>

int gcd1 (int a, int b) {
    if ( b == 0) {
        return a;
    }
    return gcd1(b, a % b);
}
int gcd2 (int a, int b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    while (a != b) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

int gcd3 (int a, int b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    int result = 1;
    for (int d = 1; d <= a && d <= b; d++) {
        if (a % d == 0 && b % d == 0) {
            result = d;
        }
    }
    return result;
}

const std::pair<int, int> testPairs[10] = {
    {48, 18},
    {1071, 462},
    {0, 987654321},
    {1073741824, 805306368},
    {1134903170, 701408733},
    {2147483647, 2147483629},
    {1000000007, 998244353},
    {2147302917, 1992491},
    {2000000000, 1999999998},
    {1836311903, 1134903170}
};
int main() {
    std::vector<long long> durations1;
    std::vector<long long> durations2;
    std::vector<long long> durations3;
    std::vector<long long> rez1;
    std::vector<long long> rez2;
    std::vector<long long> rez3;
    for (const auto& [a, b] : testPairs) {
        auto start1 = std::chrono::high_resolution_clock::now();
        rez1.push_back(gcd1(a,b));
        auto stop1 = std::chrono::high_resolution_clock::now();
        durations1.push_back(std::chrono::duration_cast<std::chrono::nanoseconds	>(stop1 - start1).count());

        auto start2 = std::chrono::high_resolution_clock::now();
        rez2.push_back(gcd2(a,b));
        auto stop2 = std::chrono::high_resolution_clock::now();
        durations2.push_back(std::chrono::duration_cast<std::chrono::nanoseconds	>(stop2 - start2).count());

        auto start3 = std::chrono::high_resolution_clock::now();
        rez3.push_back(gcd3(a,b));
        auto stop3 = std::chrono::high_resolution_clock::now();
        durations3.push_back(std::chrono::duration_cast<std::chrono::nanoseconds	>(stop3 - start3).count());
    }
    for ( auto i = 0; i < 10; i++) {
        std::cout << "Test case " << i+1 << ": (" << testPairs[i].first << ", " << testPairs[i].second << ")\n";
        std::cout << "gcd1 result: " << rez1[i] << " duration: " << durations1[i] << " nanoseconds\n";
        std::cout << "gcd2 result: " << rez2[i] << " duration: " << durations2[i] << " nanoseconds\n";
        std::cout << "gcd3 result: " << rez3[i] << " duration: " << durations3[i] << " nanoseconds\n";
        std::cout << "\n";
    }
    
    return 0;
}
