#include <stdio.h>
#include <math.h>
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
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases TCS is within valid range

    for (int TC = 1; TC <= TCS; ++TC) {
        long long k;
        scanf("%lld", &k);
        assert(k >= 1 && k <= 1000000000000000000); // PRE: k is within valid range

        long long lo = k, hi = 2 * k;
        long long ans = hi;

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            long long p = sqrt(mid);
            long long q = mid - p;

            if (q < k)
                lo = mid + 1;
            else {
                ans = mid;
                hi = mid - 1;
            }
        }
        
        printf("%lld\n", ans);
        assert(ans >= k); // POST: The minimum number of bulbs n is at least k
    }
    return 0;
}