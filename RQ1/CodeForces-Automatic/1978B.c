#include <stdio.h>
#include <assert.h>

long long min(long long x, long long y) {
    return (x < y) ? x : y;
}

int main() {
    int TCS = 0;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4

    for (int TC = 1; TC <= TCS; ++TC) {
        long long n, a, b;
        scanf("%lld %lld %lld", &n, &a, &b);
        assert(n >= 1 && n <= 1000000000); // PRE: 1 <= n <= 10^9
        assert(a >= 1 && a <= 1000000000); // PRE: 1 <= a <= 10^9
        assert(b >= 1 && b <= 1000000000); // PRE: 1 <= b <= 10^9
        
        long long ans;
        if (a > b) {
            ans = n * a;
        } else {
            long long k = min(b - a, n);
            long long r = b - k;
            ans = (b * b + b) / 2 - (r * r + r) / 2;
            if (k < n)
                ans += a * (n - k);
        }
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: ans >= 0, profit can't be negative
    }
    return 0;
}