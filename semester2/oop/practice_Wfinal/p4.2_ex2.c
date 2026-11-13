#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v{10, 9, 8, 7, 6, 5};
    vector<int>::iterator it = v.begin() + 2;
    v.erase(it);                 // removes element at index 2 (which is 8)
    it = v.begin() + 3;          // now v = {10, 9, 7, 6, 5}
    *it = 11;                    // v = {10, 9, 7, 11, 5}
    it++;
    *it = 1;                     // v = {10, 9, 7, 11, 1}

    deque<int> x;
    std::copy_if(v.begin(), v.end(), front_inserter(x),
                 [](int a) { return a % 2 == 1; });

    for (auto a : x)
        cout << a << " ";

    return 0;
}

