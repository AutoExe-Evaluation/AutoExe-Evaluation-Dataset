#include <stdio.h>
#include <assert.h>

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ TCS ≤ 10^4

    for (int TC = 1; TC <= TCS; ++TC) {
        long long x, y, k;
        scanf("%lld %lld %lld", &x, &y, &k);
        assert(x >= 1 && k >= 1 && y >= 2); // PRE: 1 ≤ x, k ≤ 10^9 and 2 ≤ y ≤ 10^9

        while (k && x > 1) {
            long long r = y - x % y;
            x += min(k, r);
            k -= min(k, r);
            while (x % y == 0) x /= y;
        }
        
        long long result = x + k % (y - 1);
        printf("%lld\n", result);
        assert(result >= 1); // POST: result should be at least 1
    }
    return 0;
}