/**
 * In the problem statement, it is said that the numbers will have up to
 * 10 digits, so we can have the number L = 0xFFFFFFFFFF = 1'099'511'627'775.
 * We will need all prime numbers less or equal to sqrt(L).
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
using i64 = long long int;

const int LIMIT      = 1'048'576; // sqrt(1'099'511'627'775) = 1048575.9
const int LIMIT_SQRT = 1'024;     // sqrt(1'048'576) = 1'024

int numbers[LIMIT + 1];
i64 primes[90'767];               // pi(1'048'576) = 90'766.52
int n;

void sieve()
{
    for (int i = 3; i <= LIMIT_SQRT; i += 2) {
        if (numbers[i] == -1) {
            continue;
        }
        for (int j = 2 * i; j < LIMIT; j += i) {
            numbers[j] = -1;
        }
    }

    primes[0] = 2;
    n = 1;
    for (int i = 3; i < LIMIT; i += 2) {
        if (numbers[i] == 0) {
            primes[n++] = static_cast<i64>(i);
        }
    }
}

inline bool isPrime(const i64 &p)
{
    int  i;
    bool b;

    if (p <=  1ll) {
        b = false;
    } else {
        b = true;
        while ( (primes[i] * primes[i] <= p) && b && (i < n) ) {
            b = (p % primes[i] != 0);
            ++i;
        }
    }

    return b;
}

inline bool isHexPrime(const string &s)
{
    return isPrime(strtoll(s.c_str(), nullptr, 16));
}

inline bool isDecPrime(const string &s)
{
    return isPrime(strtoll(s.c_str(), nullptr, 10));
}

inline bool isOctPrime(const string &s)
{
    return isPrime(strtoll(s.c_str(), nullptr, 8));
}

inline bool isBinPrime(const string &s)
{
    return isPrime(strtoll(s.c_str(), nullptr, 2));
}

int gcd(int a, int b)
{
    int r;

    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main()
{
    int    t, num, denom, g;
    bool   decNumber, octNumber, binNumber;
    string s;

    sieve();
    cin >> t;
    while(t > 0) {
        cin >> s;
        decNumber = all_of(s.begin(), s.end(), [](const char &ch) -> bool {
            return ch >= '0' && ch <= '9';
        });
        octNumber = all_of(s.begin(), s.end(), [](const char &ch) -> bool {
            return ch >= '0' && ch <= '7';
        });
        binNumber = all_of(s.begin(), s.end(), [](const char &ch) -> bool {
            return ch == '0' || ch <= '1';
        });

        num = (int) isHexPrime(s)
                + (int) (decNumber && isDecPrime(s))
                + (int) (octNumber && isOctPrime(s))
                + (int) (binNumber && isBinPrime(s));
        denom = 1 + (int) decNumber + (int) octNumber + (int) binNumber;
        g = gcd(num, denom);

        cout << (num / g) << "/" << (denom / g) << endl;
        t--;
    }

    return 0;
}

