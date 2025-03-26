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

int main() {
    long long TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is within the valid range
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 1000000000); // PRE: n is within the valid range
        printf("%lld\n", (n + 1) / 10);
        assert((n + 1) / 10 >= 0); // POST: The result is non-negative
    }
    return 0;
}