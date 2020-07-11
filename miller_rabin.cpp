/*

Code by: Pavel Sankin
github.com/Pankin610

Miller-Rabin's algroithm. Checks if X(<=10^18) is prime.
Failure probability: 1 / 4^k. k - fixed constant in the code.
Time Complexity: O( log X * k ), relatively small constant.

Possible use: Competetive Programming.

*/


#include <bits/stdc++.h>

using namespace std;

mt19937_64 rndd(1999999973);

long long mul(long long a, long long b, long long m) {
    a %= m, b %= m;
    long long q = (long long)((long double)a * (long double)b / (long double)m);
    long long res = a * b - q * m;
    while(res < 0)
        res += m;
    return res % m;
}

long long bin_pow(long long num, long long st, long long mod) {
    if (st == 0)
        return 1;
    if (st % 2 == 1)
        return mul(bin_pow(num, st - 1, mod), num, mod);
    else {
        long long qz = bin_pow(num, st / 2, mod);
        return mul(qz, qz, mod);
    }
}

bool miller_rabin(long long a, long long x) {
    int r = __builtin_ctzll(x - 1);
    long long d = x>>r;

    long long cur = bin_pow(a, d, x);
    if (cur == 1)
        return true;

    for (int i = 0; i <= r - 1; i++) {
        if (cur == x - 1)
            return true;
        cur = mul(cur, cur, x);
    }
    return false;
}

bool miller_rabin(long long x) {
    if ((x&1) == 0 || x % 3 == 0 || x == 1)
        return false;
    if (x < 10)
        return true;

    int k = 60;
    while(k--) {
        long long a = rndd();
        if (a < 0)
            a = -a;
        a %= (x - 1);
        a++;

        if (!miller_rabin(a, x))
            return false;
    }
    return true;
}
