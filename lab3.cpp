#include <iostream>
using namespace std;

long long binpow(long long a, long long n){
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return binpow(a, n - 1) * a;
    else {
        long long b = binpow(a, n / 2);
        return b * b;
    }
}

int main(){
    long long p, a, N, k = 0, p2, h, b, c, d = 9223372036854775807;
    cin >> p >> a >> N;
    p2 = p - 1;
    while (p2%2 == 0) {
        p2 = p2/2;
        k+=1;
    }
    h = (p - 1)/binpow(2, k);
    long long a1 = -binpow(a, (h + 1)/2) % p;
    long long a2 = binpow(a, -1) % p;
    long long N1 = binpow(N, h) % p;
    long long N2 = 1;
    long long j = 0;
    for (int i = 0; i <= k - 2; i++){
        b = (a1 * N2) % p;
        c = (a2 * b * b) % p;
        int d1 = binpow(c, binpow(2, k-2-i)) % p;
        if (d1 < d)
            d = d1;
        if (d = 1)
            j = 0;
        if (d = -1)
            j = 1;
        N2 = (N2*binpow(N1, 2*j)) % p;
    }
    cout << (a1*N2) % p << endl;
    cout << -(a1*N2) % p << endl;
    return 0;
}
