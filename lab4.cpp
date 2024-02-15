#include <vector>
#include <complex>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

typedef long long int ll;
using namespace std;

typedef complex<double> base;

ll binpow(long long a, long long n){
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return binpow(a, n - 1) * a;
    else {
        long long b = binpow(a, n / 2);
        return b * b;
    }
}

void FFT (vector<base> & a, bool inv) 
{
	ll n = (ll) a.size();
	if (n == 1)  
	    return;
	vector<base> A(n/2),  B(n/2);
	for (int i=0, j=0; i < n; i += 2, ++j) 
	{
		A[j] = a[i];
		B[j] = a[i + 1];
	}
	FFT (A, inv);
	FFT (B, inv);
	base w (1),  wn (cos(2*M_PI/n * (inv ? -1 : 1)), sin(2*M_PI/n * (inv ? -1 : 1)));
	for (int i = 0; i < n/2; ++i) 
	{
		a[i] = A[i] + w * B[i];
		a[i + n/2] = A[i] - w * B[i];
		if (inv)
			a[i] /= 2,  a[i + n/2] /= 2;
		w *= wn;
	}
}

vector<ll> SSA (const vector<ll> & a, const vector<ll> & b) 
{
    vector<ll> res;
	vector<base> FurA (a.begin(), a.end());
	vector<base> FurB (b.begin(), b.end());
	size_t n = 1, i;
	ll tmp = 0;
	while (n < max(a.size(), b.size()))  
	    n <<= 1;
	n <<= 1;
	FurA.resize(n);  
	FurB.resize(n);
	FFT (FurA, 0);
	FFT (FurB, 0);
	
	for (i = 0; i < n; ++i)
		FurA[i] *= FurB[i];
	FFT (FurA, 1);
 
	res.resize(n);
	for (i = 0; i < n; ++i)
		res[i] = ll (FurA[i].real() + 0.5);
    
	for (i=0; i < n; ++i)
	{
		res[i] += tmp;
		tmp = res[i] / 10;
		res[i] %= 10;
	}
	return res;
}

int main()
{
    string c1, c2;
    vector<ll> a, b, res;
    
    cout << "Введите a и b: ";
    cin  >> c1 >> c2;
    
    for (ll i = c1.size() - 1;i != -1; i --)
        a.emplace_back(c1[i] - 0x30);
    
    for (ll i = c2.size() - 1;i != -1; i --)
        b.emplace_back(c2[i] - 0x30);

    res = SSA(a, b);
    cout << c1 << "*" << c2 << " = ";

    int R = 0;
    for (ll i = res.size(); i>=0; i--)
    {   
        if (res[i] || R)
        {
            R = 1;
            cout << res[i];
            
        }
    }

}
