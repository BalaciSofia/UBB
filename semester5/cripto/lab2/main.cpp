#include <iostream>
#include <vector>

std::vector<int> compute(int n) {
    // allocate space and initialize as true
    std::vector<bool> prime(n + 1, true);
    // loop until square root of n
    for (int p = 2; p * p <= n; p++) {
        //if it s prime, mark all multiples as false
        if (prime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    //get all the prime numbers in a vector
    std::vector<int> res;
    for (int p = 2; p <= n; p++){
        if (prime[p]){
            res.push_back(p);
        }
    }
    return res;
}
int main() {
    int n;
    std::cout << "n= ";
    std::cin>>n;
    std::vector<int> res = compute(n);
    for(auto elem : res){
        std::cout << elem << ' ';
    }
    return 0;
}
