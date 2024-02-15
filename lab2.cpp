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
    long long a, n, g = 1, a1, s;
    cout << "Enter a and n separated by a space" << endl;
    cin >> a >> n;
    if (n%2==0 || n<3) {
        cout << "Incorrect data";
        return 0;
    }
    while(true){
        if (a == 0) {
            cout << "Jacobi symbol: " << 0 << endl;
            return 0;
        }
        if (a == 1) {
            cout << "Jacobi symbol: " <<  g << endl;
            return 0;
        }
        long long k = 0, a2 = a;
        while (a2%2 == 0) {
            a2 = a2/2;
            k+=1;
        }
        a1 = a/binpow(2, k);
        if (k%2==0)
            s = 1;
        if (k%2==1){
            if (n%8==1||n%8==7)
                s = 1;
            if (n%8==3||n%8==5)
                s = -1;
        }
        if (a1==1){
            cout << "Jacobi symbol: " << g*s << endl;
            return 0;
        }
        if (n%4==3&&a1%4==3)
            s = -s;
        a = n%a1;
        n = a1;
        g = g*s;
    }
}
