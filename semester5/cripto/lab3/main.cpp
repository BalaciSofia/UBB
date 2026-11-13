#include <iostream>
#include <cmath>
#include <numeric>   // gcd
using namespace std;

//problem 3

bool isSquare(long long n) {
    if (n < 0) return false;
    long long root = sqrt(n);
    return root * root == n;
}

//any odd number can be written as a difference of 2 squares
//
int main() {
    long long B; // suitable bound
    long long n; // odd composite number which is not a square
    cout<<"input n: ";
    cin>>n;
    cout<<"input B: ";
    cin>>B;

    int k=1;
    while (true){
        //k = 1, 2, 3 ...
        long long t0 = sqrt(k*n);
        for (long long t = t0 + 1 ; t <= t0 + B; t++) {
            if (isSquare(t * t - k*n)) {
                long long s = sqrt(t * t - k*n);
                long long d1 = gcd(t - s, n);
                long long d2 = gcd(t + s, n);

                if (1 < d1 && d1 < n) {
                    cout << "k = " << k << endl;
                    cout << "t = " << t << endl;
                    cout << "n = " << d1 << " * " << n / d1 << endl;
                    return 0;
                }
                if (1 < d2 && d2 < n) {
                    cout << "k = " << k << endl;
                    cout << "t = " << t << endl;
                    cout << " n = " << d2 << " * " << n / d2 << endl;
                    return 0;
                }
            }
        }
        k++;
    }
}
