#include <stdio.h>
#include <assert.h>

long long pow(long long x, long long y, long long m) {
    long long ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int is_prime(long long n) {
    if (n < 2) return 0;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int TCS;
    assert(TCS >= 1 && TCS <= 5); // PRE: number of test cases must be between 1 and 5
    scanf("%d", &TCS);
    for (int TC = 1; TC <= TCS; ++TC) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        assert(b < a && a <= 100000000000); // PRE: 1 <= b < a <= 10^11
        if (a - b > 1) {
            printf("NO\n");
            continue;
        }
        long long n = a + b;
        printf(is_prime(n) ? "YES\n" : "NO\n");
    }
    return 0;
} // POST: for valid inputs, program outputs whether the area of the cloth is prime or not.