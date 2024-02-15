#include <iostream>
using namespace std;
long long gcd(long long a, long long b, long long& x, long long& y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    long long g = gcd(b, a % b, x, y);
    x -= (a / b) * y;
    swap(x, y);
    return g;
}
 
int main(){
    long long a, b, c, x, y, g, x0, y0, a0, b0, Q[1000], t, p3, p2 = 0, p1 = 1, Q3 , Q2 = 1, Q1 = 0, tmp;
    cout << "Enter coefficient a: ";
    cin >> a;
    cout << "Enter coefficient b: ";
    cin >> b;
    cout << "Enter coefficient c: ";
    cin >> c;
    g = gcd(a, b, x, y);
    if (c == g){
        a0 = a / g;
        b0 = b / g;
        cout << "Solution" << endl;
        if (a0 < b0) {
            swap (a0, b0);
            Q[0] = 0;
            t = 1;
            }
        while (a0 % b0 != 0) {
            Q[t] = a0 / b0;
            a0 = a0 % b0;
            swap (a0, b0);
            t++;
        }
        for (long long i = 0; i < t; i++) {
            p3 = Q[i] * p1 + p2;
            Q3 = Q[i] * Q1 + Q2;
            p2 = p1;
            p1 = p3;
            Q2 = Q1;
            Q1 = Q3;
        }
        if (t % 2 == 0) {
            Q3 *= -1;
            p3 *= -1;
        }
        cout << "x: " << Q3 << " y: " << p3;
    }
    else cout << "There is no solution";
    return 0;
}
