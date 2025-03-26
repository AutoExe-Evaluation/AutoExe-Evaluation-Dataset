#include <stdio.h>
#include <assert.h>

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4
    
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long x, y, k;
        scanf("%lld %lld %lld", &x, &y, &k);
        assert(x >= 0 && x <= 1000000000); // PRE: 0 <= x <= 10^9
        assert(y >= 0 && y <= 1000000000); // PRE: 0 <= y <= 10^9
        assert(k >= 1 && k <= 1000000000); // PRE: 1 <= k <= 10^9
        
        long long p = (x + k - 1) / k;
        long long q = (y + k - 1) / k;
        long long ans = 2 * max(p, q);
        if (p > q) ans--;
        printf("%lld\n", ans);

        assert(ans >= 0); // POST: ans is non-negative
    }
    
    return 0;
}