#include<bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <numeric>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>


#define DEBUG 0

using namespace std;
typedef long long int ll;

//-------------------DES-------------------------

const int IP[64] = { 58,50,42,34,26,18,10,2,
                     60,52,44,36,28,20,12,4,
                     62,54,46,38,30,22,14,6,
                     64,56,48,40,32,24,16,8,
                     57,49,41,33,25,17, 9,1,
                     59,51,43,35,27,19,11,3,
                     61,53,45,37,29,21,13,5,
                     63,55,47,39,31,23,15,7 };

const int IP_1[64] = { 40,8,48,16,56,24,64,32,
                       39,7,47,15,55,23,63,31,
                       38,6,46,14,54,22,62,30,
                       37,5,45,13,53,21,61,29,
                       36,4,44,12,52,20,60,28,
                       35,3,43,11,51,19,59,27,
                       34,2,42,10,50,18,58,26,
                       33,1,41,9,49,17,57,25 };

const int E_exp[48] = { 32,1,2,3,4,5,
                        4,5,6,7,8,9,
                        8,9,10,11,12,13,
                        12,13,14,15,16,17,
                        16,17,18,19,20,21,
                        20,21,22,23,24,25,
                        24,25,26,27,28,29,
                        28,29,30,31,32,1};

const int P_transform[32] = { 16,7,20,21,
                              29,12,28,17,
                              1,15,23,26,
                              5,18,31,10,
                              2,8,24,14,
                              32,27,3,9,
                              19,13,30,6,
                              22,11,4,25};

const int PC_1[56] = { 57,49,41,33,25,17,9,
                       1,58,50,42,34,26,18,
                       10,2,59,51,43,35,27,
                       19,11,3,60,52,44,36,
                       63,55,47,39,31,23,15,
                       7,62,54,46,38,30,22,
                       14,6,61,53,45,37,29,
                       21,13,5,28,20,12,4};

const int PC_2[56] = { 14,17,11,24,1,5,
                       3,28,15,6,21,10,
                       23,19,12,4,26,8,
                       16,7,27,20,13,2,
                       41,52,31,37,47,55,
                       30,40,51,45,33,48,
                       44,49,39,56,34,53,
                       46,42,50,36,29,32};

const int SBOX_1[4][16] = {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                           {0,15,7,4,15,2,13,1,10,6,12,11,9,5,3,8},
                           {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                           {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};

const int SBOX_2[4][16] = {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                           {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                           {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                           {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}};

const int SBOX_3[4][16] = {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                           {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                           {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                           {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}};

const int SBOX_4[4][16] = {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                           {12,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                           {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                           {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}};

const int SBOX_5[4][16] = {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                           {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                           {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                           {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}};

const int SBOX_6[4][16] = {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                           {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                           {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                           {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}};

const int SBOX_7[4][16] = {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                           {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                           {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                           {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}};

const int SBOX_8[4][16] = {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                           {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                           {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                           {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};

typedef const int (*SBOX)[16];
SBOX SBox[8] = { SBOX_1, SBOX_2, SBOX_3, SBOX_4, SBOX_5, SBOX_6, SBOX_7, SBOX_8};

class DES{
private:
    string total_code, total_key;
    string tempCode_1, tempCode_2;
    string m_code, code;
    string L, R, C, D;
    vector<string> K;
public:
    DES() {}
    // шифрование
    void encode(string str, string key, bool G) {
        m_code = "";
        total_code = str;
        total_key = key;
        if(DEBUG) {
            cout << "getkeys" << endl;
        }
        getKeys();
        if(DEBUG) {
            cout << "formatSourceCode" << endl;
        }
        formatSourceCode();
        int count = 0;
        int s = total_code.size();
        while(count*8 < s) {
            string sub;
            if(s-count*8 >= 8){
                sub = total_code.substr(count*8, 8);
            }
            else{
                sub = total_code.substr(count*8);
            }
            count++;
            fill(sub);
            if(DEBUG) {
                cout << "code length: "<< tempCode_1.size() << endl;
            }
            if(DEBUG) {
                cout << "IP0" << endl;
            }
            getIP0();
            if(DEBUG) {
                cout << "iterationT" << endl;
            }
            string a = iterationT_A(1, 16);
            if(DEBUG) {
                cout << "IP1" << endl;
            }
            string result = getIP1(a);
            m_code += result;
            if(DEBUG) {
                cout << result.size() << endl;
            }
        }
        if (G)
            cout << m_code << endl;
    }
    // расшифровать
    void decode(string str, string key) {
        int count = 0;
        code = "";
        getKeys();
        while(count*64 < str.size()){
            tempCode_1 = str.substr(count*64, 64);
            total_key = key;
            count++;
            if(DEBUG) {
                cout << "K :" << endl;
                for(int i = 0; i < K.size(); i++) {
                    cout << K[i] <<endl;
                }
                cout << "IP0" << endl;
            }
            getIP0();
            if(DEBUG) {
                cout << "iterationT" << endl;
            }
            string a = iterationT_D(16, 1);
            if(DEBUG) {
                cout << "IP1" << endl;
            }
            string result = getIP1(a);
            if(count*64 == str.size()) {
                code += formatAndReduceResult(result);
            }
            else {
                code += formatResult(result);
            }
        }
        cout << code << endl;
    }
    // часть пароля
    // заполняем строку
    void fill(string str) {
        tempCode_1 = "";
        for(int i = 0; i < 8; i++) {
            string s;
            int a = i < str.size()? (int)str[i] : 8-str.size();
            while(a > 0) {
                s = (char)(a%2+48) + s;
                a /= 2;
            }
            while(s.size() < 8) {
                s = "0" + s;
            }
            tempCode_1 += s;
        }
        if(DEBUG) {
            cout << tempCode_1 << endl;
        }
    }
    // заполняем строку
    void formatSourceCode() {
        if(total_code.size() % 8 == 0) {
            total_code += "\b\b\b\b\b\b\b\b";
        }
    }
    // Замена IP (LR)
    void getIP0() {
        tempCode_2 = tempCode_1;
        L = "";
        R = "";
        for(int i = 0; i < 64; i++) {
            tempCode_2[i] = tempCode_1[IP[i]-1];
        }
        for(int i = 0; i < 64; i++) {
            if(i < 32){
                L += tempCode_2[i];
            }
            else {
                R += tempCode_2[i];
            }
        }

        if(DEBUG) {
            cout << "tempCode_2: " << tempCode_2 << endl;
            cout << "L: " << L << endl;
            cout << "R: " << R << endl;
        }
    }
    // Круглая функция Фейстеля
    string Feistel(string R, string K) {
        string res = "", rec = "";
        // E-расширение строки Ri-1 до 32 бит
        string ER = E_expend(R);
        // E (Ri-1) и подключ Ki длиной 48 бит подвергаются операции XOR
        for(int i = 0; i < 48; i++) {
            res += (char)(((ER[i]-48) ^ (K[i]-48))+48);
        }
        // Равномерно разделить на 8 групп и пройти через 8 разных S-блоков для преобразования 6-4
        for(int i = 0; i < 8; i++) {
            string sub = res.substr(i*6, 6);
            string sub_m = Feistel_SBOX(sub, i);
            // Подключаемся последовательно, чтобы получить строку длиной 32 бита
            rec += sub_m;
        }
        if(DEBUG) {
            cout << "substring length: " << rec.size() << endl;
        }
        // P- перестановка
        return getPTransform(rec);
    }
    // P замена
    string getPTransform(string str) {
        string res = "";
        for(int i = 0; i < 32; i++) {
            res += str[P_transform[i]-1];
        }
        return res;
    }
    // Feistel SBOX
    string Feistel_SBOX(string str, int num){
        int n = (str[0]-48) * 2 + (str[5]-48);
        int m = (str[1]-48) * 8 + (str[2]-48) * 4 + (str[3]-48) * 2 + (str[4]-48);
        int number = SBox[num][n][m];
        string res = "";
        while(number > 0) {
            res = (char)(number%2+48) + res;
            number /= 2;
        }
        while(res.size() < 4) {
            res = "0" + res;
        }
        if(DEBUG) {
            cout << "SBox: " << endl;
            cout << str << " " << num << " " << res << endl;
        }
        return res;
    }
    // Расширение E
    string E_expend(string str) {
        string res = "";
        for(int i = 0; i < 48; i++) {
            res += str[E_exp[i]-1];
        }
        if(DEBUG) {
            cout << "E expend: " << res << endl;
        }
        return res;
    }
    // операция XOR
    string XORoperation(string a, string b) {
        string res = "";
        for(int i = 0; i < 32; i++) {
            res += (char)(((a[i]-48) ^ (b[i]-48))+48);
        }
        return res;
    }
    // Т итерация (зашифрованная)
    string iterationT_A(int begin, int end) {
        string L_temp, R_temp;
        for(int i = begin-1; i <= end-1; i++) {
            L_temp = R;
            R_temp = XORoperation(L, Feistel(R, K[i]));
            L = L_temp;
            R = R_temp;
        }
        return R+L;
    }
    // T итерация (расшифрована)
    string iterationT_D(int begin, int end) {
        string L_temp, R_temp;
        for(int i = begin-1; i >= end-1; i--) {
            L_temp = R;
            R_temp = XORoperation(L, Feistel(R, K[i]));
            L = L_temp;
            R = R_temp;
        }
        return R+L;
    }
    // Обратная замена IP
    string getIP1(string str) {
        string res = "";
        for(int i = 0; i < 64; i++) {
            res += str[IP_1[i]-1];
        }
        return res;
    }
    // сортируем открытый текст 1
    string formatResult(string str) {
        int count = 0;
        string res = "";
        while(count*8 < str.size()) {
            string a = str.substr(count*8, 8);
            res += (char)(Two2Ten(a));
            count++;
        }
        return res;
    }
    // сортируем открытый текст 2
    string formatAndReduceResult(string str) {
        int count = 0;
        string res = "";
        string a = str.substr(str.size()-8, 8);
        int n = (int)(Two2Ten(a));
        if(DEBUG) {
            cout << a << endl;
            cout << n << endl;
        }
        while(count < 8-n) {
            a = str.substr(count*8, 8);
            res += (char)(Two2Ten(a));
            count++;
        }
        return res;
    }
    // Двоичное в десятичное
    int Two2Ten(string num) {
        int base = 1;
        int res = 0;
        for(int i = num.size()-1; i >= 0; i--) {
            res += (int)(num[i]-48) * base;
            base *= 2;
        }
        return res;
    }
    // часть подраздела
    // Формат подключа
    string formatKey() {
        string res = "", rec = "";
        for(int i = 0; i < 8; i++) {
            int num = (int)total_key[i];
            res = "";
            while(num > 0) {
                res = (char)(num%2+48) + res;
                num /= 2;
            }
            while(res.size() < 8) {
                res = "0" + res;
            }
            rec += res;
        }
        if(DEBUG) {
            cout << "rec: " << rec << endl;
        }
        return rec;
    }
    // Замена ПК1
    string getPC1Key(string str) {
        string res = str;
        for(int i = 0; i < 56; i++) {
            res[i] = str[PC_1[i]-1];
        }
        if(DEBUG){
            cout << "res: " << res << endl;
        }
        return res;
    }
    // Получаем C, D
    void get_C_D(string str) {
        C = "";
        D = "";
        str.erase(63,1);
        str.erase(55,1);
        str.erase(47,1);
        str.erase(39,1);
        str.erase(31,1);
        str.erase(23,1);
        str.erase(15,1);
        str.erase(7,1);
        for(int i = 0; i < str.size(); i++) {
            if(i < 28) {
                C += str[i];
            }
            else {
                D += str[i];
            }
        }
        if(DEBUG) {
            cout << "C: " << C << endl;
            cout << "D: " << D << endl;
        }
    }
    // Замена LS
    void getKeyI() {
        for(int i = 1; i <= 16; i++) {
            if(i == 1 || i == 2 || i == 9 || i == 16) {
                LS_1(C);
                LS_1(D);
            }
            else {
                LS_2(C);
                LS_2(D);
            }
            string t = C+D;
            t = getPC2Key(t);
            K.push_back(t);
        }
    }
    // LS перестановка (1)
    void LS_1(string& str) {
        char a = str[0];
        for(int i = 0; i < str.size()-1; i++) {
            str[i] = str[i+1];
        }
        str[str.size()-1] = a;
    }
    // LS перестановка (2)
    void LS_2(string& str) {
        char a = str[0], b = str[1];
        for(int i = 0; i < str.size()-2; i++) {
            str[i] = str[i+2];
        }
        str[str.size()-2] = a;
        str[str.size()-1] = b;
    }
    // Замена ПК2
    string getPC2Key(string str) {
        string res = str;
        for(int i = 0; i < 48; i++) {
            res[i] = str[PC_2[i]-1];
        }
        res.erase(53,1);
        res.erase(42,1);
        res.erase(37,1);
        res.erase(34,1);
        res.erase(24,1);
        res.erase(21,1);
        res.erase(17,1);
        res.erase(8,1);
        return res;
    }
    // Получаем общую функцию подраздела
    void getKeys() {
        vector<string> t;
        K = t;
        string a = formatKey();
        a = getPC1Key(a);
        get_C_D(a);
        getKeyI();
    }
};
//-----------------------------------------------

//-------------------RSA-------------------------
bool isSmaller(string str1, string str2)
{
  int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2)
    return true;
    if (n2 < n1)
    return false;

    for (int i=0; i<n1; i++)
    if (str1[i] < str2[i])
        return true;
    else if (str1[i] > str2[i])
        return false;

    return false;
}
string longDivision(string number,ll divisor)
{
	string ans;
	int idx = 0;
	int temp = number[idx] - '0';
	while (temp < divisor)
	temp = temp * 10 + (number[++idx] - '0');
	while (number.size() > idx)
	{
		ans += (temp / divisor) + '0';
		temp = (temp % divisor) * 10 + number[++idx] - '0';
	}
	if (ans.length() == 0)
		return "0";
	return ans;
}
string findDiff(string str1, string str2)
{
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n2; i++)
    {
        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry);
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        str.push_back(sub + '0');
    }
    for (int i=n2; i<n1; i++)
    {
        int sub = ((str1[i]-'0') - carry);
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        str.push_back(sub + '0');
    }
    reverse(str.begin(), str.end());
    str.erase(0, min(str.find_first_not_of('0'), str.size()-1));

    return str;
}
string multiply(string num1, string num2) // TODO: Schönhage–Strassen
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";
    vector<int> result(len1 + len2, 0);
    int i_n1 = 0;
    int i_n2 = 0;
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
        i_n2 = 0;
        for (int j=len2-1; j>=0; j--)
        {   int n2 = num2[j] - '0';
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
            carry = sum/10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n1++;
    }
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
    if (i == -1)
    return "0";
    string s = "";
    while (i >= 0)
        s +=(result[i--])+'0';
    return s;
}
ll mod(string num, ll a)
{
	int res = 0;
	for (int i = 0; i < num.length(); i++)
		res = (res*10 + (int)num[i] - '0') %a;
	return res;
}
string findSum(string str1, string str2)
{
    if (str1.length() > str2.length())
        swap(str1, str2);
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry)
        str.push_back(carry+'0');
    reverse(str.begin(), str.end());
    return str;
}
ll gcd(ll a, ll b)
{
	if (!a)
	return b;
	return gcd(b%a,a);
}
ll reduceB(ll a, string b)
{
	ll mod = 0;
	for (int i=0; i<b.length(); i++)
		mod = (mod*10 + b[i] - '0')%a;

	return mod;
}
ll gcdLarge(ll a, string b)
{
	ll num = reduceB(a,b);
	return gcd(a, num);
}
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}
string moduloequallengths(string str1,string str2)
{	string res1="",c="";

		string a;
		for (int i = 9; i >=1; i--)
		{
			a=i+'0';
			c=multiply(str2,a);
			if(isSmaller(str1,c))
				continue;
			else
			{
				res1=findDiff(str1,c);
				break;
			}
		}
		return res1;
}
string modulo(string str1,string str2)
{	string req;
	string res="";

	int l1=str1.length(),l2=str2.length();

	if(isSmaller(str1,str2)==1)
		return str1;
	if(l1==l2)
	{
		return moduloequallengths(str1,str2);
	}
	else
	{
		string str2a=str2;
		int l=str2a.length();
		string str=str1.substr(0,l);
		if(isSmaller(str,str2a)!=1)
		{
			req=moduloequallengths(str,str2a);
			req+=str1.substr(l);
		}
		else
		{	str+=str1.substr(l,1);
            reverse(str2a.begin(),str2a.end());
            str2a+="0";
            reverse(str2a.begin(),str2a.end());
            req=moduloequallengths(str,str2a);
			req+=str1.substr(l+1);
		}
		}
	return modulo(req,str2);
}
string exponentMod(string str1,string str2,string str3)
{
	if(str1=="0")
		return 0;
	if(str2=="0")
		return "1";
	string y;
	if(mod(str2,2)==0)
	{
		y=exponentMod(str1,longDivision(str2,2),str3);
		y=modulo(multiply(y,y),str3);
	}
	else
	{
		y=modulo(str1,str3);
		y=modulo(multiply(y,modulo(exponentMod(str1,findDiff(str2,"1"),str3),str3)),str3);
	}

	return (string)(modulo(findSum(y,str3),str3));
}
//-----------------------------------------------

long long GF(long long a, long long b){
    long long X = 1, X1 = 0, q, r, X2, tmp, b1=b;
    while (b != 0){
        q = a / b;
        r = a % b;
        X2 = X - q * X1;
        a = b;
        b = r;
        X = X1;
        X1 = X2;
    }
    if (X < 0)
        X += b1;
    cout << X << endl;
    return X;
}

long long binpow(long long a, long long n, long long p){
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return (binpow(a, n - 1, p) * a) % p;
    else {
        long long b = binpow(a, n / 2, p);
        return (b * b) % p;
    }
}

int main()
{   
    srand( time( 0 ) );
    long long X;
    cout << "IPSec" << endl;
    cout << "Запустить сервер(1)/ Запустить клиент(2): ";
    cin >> X;
    if(X == 1){
        //-------------------RSA GEN------------------AH
        //long long p = 96479, q = 21149, n ,f, e, x, Q, P; // TODO: генерация p q
        //n = p * q; //TODO: Шенхаге-Штрассен
        //f = (p - 1) * (q - 1); //TODO: Шенхаге-Штрассен
        //e = f;
        //while(gcd(e, f) != 1)
        //    e = rand() % f; // закрытый ключ
        //x = GF(e, f);
        //Q = rand(); // Открытый ключ для Диффи-Хелмана
        //P = rand(); // Открытый ключ для Диффи-Хелмана
        //cout << "Q: " << Q << " P: " << P << endl;
        //cout << "Открытый ключ RSA e, n: " << e_d << " " << n << endl;
        
        string p = "996446807922616646684800009925630715566661499541880099431687048860752807586487989864469109098383247376606384751122301037",
        q = "745864326564093662438329296905178217810009353605944262276045622290653238146364800152018551643225955064484302032477064669",
        n,f,x, e_d;
        ll e = 3;
        n = multiply(p, q);
        p = findDiff(p,"1");
        q = findDiff(q,"1");
        f = multiply(p,q);
        string temp_phi=f;
	    temp_phi[f.length()]='\0';
	    while(1) {
		    if((gcdLarge(e,temp_phi) == 1))
			    break;
			e += 2;
	    }
        ll i=0, qs=0;
	    char rev_iter_no[1000];
	    string ino;
	    string y;
		do{
			i++;

			ll j = i, k1 = 0;
			while(j!=0)
			{
				rev_iter_no[k1]=char((j%10)+'0');
				k1++;
				j/=10;
			}
			rev_iter_no[k1]='\0';
			ino=convertToString(rev_iter_no,k1);
			reverse(ino.begin(),ino.end());

			y=multiply(ino,temp_phi);
			qs=mod(y,e);
		}while(qs != e - 1);
	    y = findSum(y,"1");
	    x = longDivision(y,e);
	    e_d = std::to_string(e);
        ll Q, P;
        string Q1, P1;
        Q = rand(); // Открытый ключ для Диффи-Хелмана
        P = rand(); // Открытый ключ для Диффи-Хелмана
        Q1 = std::to_string(Q);
        P1 = std::to_string(P);
        cout << "Q: " << Q1 << " P: " << P1 << endl;
        cout << "Открытый ключ RSA e, n: " << e_d << " " << n << endl;
        //-------------------RSA ENC------------------
        //long long C1, C2;
        //C1 = binpow(Q, e, n) % n;
        //C2 = binpow(P, e, n) % n;
        string C1, C2;
        C1 = exponentMod(Q1,x,n);
        C2 = exponentMod(P1,x,n);
        cout << "Зашифрованный открытый ключ DH: " << C1 << " " << C2 << endl;
        //-------------------DH ENC-------------------IKE
        long long a, Ya, Yb, k;
        Q = atoi(Q1.c_str());
        P = atoi(P1.c_str());
        a = rand();
        Ya = binpow(Q, a, P);
        cout << "Ya: " << Ya << endl;
        cout << "Введите Yb: ";
        cin >> Yb;
        k = binpow(Yb, a, P); //Ключ для DES
        cout << k << endl;
        //-------------------DES ENC------------------ESP
        string c;
        cout << "Введите ваше сообщение: ";
        cin.ignore(1, '\n');
        getline(cin, c);
        DES des;
        cout << "Зашифрованное сообщение: ";
        des.encode(c, to_string(k), 1);
    }
    if(X == 2){
        //-------------------RSA PRE------------------AH
        //long long n, x, Q, P;
        string e, n, Q1, P1;
        cout << "Введите открытый ключ RSA (e, n): ";
        cin >> e >> n;
        //-------------------RSA DEC------------------
        string C1, C2;
        cout << "Введит зашифрованный открытй ключ DH: " << " ";
        cin >> C1 >> C2;
        Q1 = exponentMod(C1,e,n);
        P1 = exponentMod(C2,e,n);
        //Q = binpow(C1, x, n); // Расшифрованный открытый ключ для Диффи-Хелмана
        //P = binpow(C2, x, n); // Расшифрованный открытый ключ для Диффи-Хелмана
        cout << "Q: " << Q1 << " P: " << P1 << endl;
        ll Q, P;
        Q = atoi(Q1.c_str());
        P = atoi(P1.c_str());
        //-------------------DH ENC-------------------IKE
        long long b, Ya, Yb, k;
        b = rand();
        Yb = binpow(Q, b, P);
        cout << "Yb: " << Yb << endl;
        cout << "Введите Ya: ";
        cin >> Ya;
        k = binpow(Ya, b, P); //Ключ для DES
        cout << k << endl;
        //-------------------DES DEC------------------ESP
        string c;
        cout << "Введите зашифрованное сообщение: ";
        cin >> c;
        DES des;
        des.encode("0", to_string(k), 0);
        cout << "Расшифрованное сообщение: ";
        des.decode(c, to_string(k));
    }
    if(X != 1 and X != 2)
        cout << "Ошибка значения!";
    return 0;
}
