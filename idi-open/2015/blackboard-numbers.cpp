#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdint>
#include <bitset>

using namespace std;

const int32_t LIMIT      = 1048576; // sqrt(1099511627775) = 1048575.9
const int32_t LIMIT_SQRT = 1024;    // sqrt(1048576) = 1024

int numbers[LIMIT + 1];
int primes[90767];                  // pi(1048576) = 90766.52
int n;

void sieve()
{
    for (int i = 2; i <= LIMIT_SQRT; ++i) {
        if (numbers[i] == -1) {
            continue;
        }
        for (int j = 2 * i; j < LIMIT; j += i) {
            numbers[j] = -1;
        }
    }

    for (i = 2; i < LIMIT; ++i) {
        if (numbers[i] == 0) {
            primes[n++] = i;
        }
    }
}

inline bool isPrime(int64_t p)
{
    int i;
    bool b;

    if (p == 0 || p == 1) {
        b = false;
    } else {
        if (p == 2 || p == 3) {
            b = true;
        } else {
            b = true;
            while ( (primes[i] * primes[i] <= p) && b && (i < n) )
                b = (p % primes[i++] != 0);
        }
    }

    return b;
}

inline bool isHexPrime(const string &s)
{
    istringstream iss;
    int64_t x;

    iss.str(s);
    iss >> setbase(16);
    iss >> x;

    return isPrime(x);
}

inline bool isDecPrime(const string &s)
{
    istringstream iss;
    int64_t x;

    iss.str(s);
    iss >> x;

    return isPrime(x);
}

inline bool isOctPrime(const string &s)
{
    istringstream iss;
    int64_t x;

    iss.str(s);
    iss >> setbase(8);
    iss >> x;

    return isPrime(x);
}

inline bool isBinPrime(const string &s)
{
    bitset<40> bs(s);

    return isPrime(bs.to_ullong());
}

int main()
{
    int    t, num, denom;
    bool   hexChar, decChar, octChar, binChar;
    string s;

    sieve();
    cin >> t;
    cin.ignore();
    while(t > 0) {
        getline(cin, s);

        num = denom = 0;
        hexChar = decChar = octChar = binChar = false;
        for(const char &c : s) {
            if (!hexChar)
                hexChar = (c >= 'A') && (c <= 'F');
            if (!decChar)
                decChar = (c == '8') || (c == '9');
            if (!octChar)
                octChar = (c >= '2') && (c <= '7');
        }
        binChar = !hexChar && !decChar && !octChar == false;

        // The number is always in hexadecimal
        if (isHexPrime(s)) {
             num++;
        }

        if (hexChar) {
            decChar = octChar = binChar = false;
            denom = 1;
        }

        if (decChar) {
            octChar = binChar = false;
            denom = 2;
            if (isDecPrime(s))
                num++;
        }

        if (octChar) {
            binChar = false;
            denom = 3;
            if (isDecPrime(s)) num++;
            if (isOctPrime(s)) num++;
        }

        if (binChar) {
            denom = 4;
            if (isDecPrime(s)) num++;
            if (isOctPrime(s)) num++;
            if (isBinPrime(s)) num++;
        }

        // Fraction reduction
        if (denom == num) {
            denom = num = 1;
        } else {
            if (denom == 4 && num == 2) {
                denom = 2;
                num = 1;
            } else {
                if(num == 0) {
                    denom = 1;
                }
            }
        }

        // Result output.
        cout << num << "/" << denom << endl;
        t--;
    }

    return 0;
}
