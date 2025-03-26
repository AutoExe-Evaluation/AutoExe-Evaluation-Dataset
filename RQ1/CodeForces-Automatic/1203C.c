#include <stdio.h>
#include <assert.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    long long n, g = 0, ans = 0;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 400000); // PRE: n is within the specified limits

    for (long long i = 0; i < n; ++i) {
        long long x;
        scanf("%lld", &x);
        assert(x >= 1 && x <= 1000000000000); // PRE: each a_i is within the specified limits
        g = gcd(g, x);
    }

    for (long long i = 1; i * i <= g; ++i) {
        if (g % i == 0) {
            ans++;
            if (i != g / i) ans++;
        }
    }
    
    printf("%lld\n", ans);
    assert(ans > 0); // POST: number of common divisors is positive
    return 0;
}