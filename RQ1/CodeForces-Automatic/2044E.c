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
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4
    while (TCS--) {
        long long k, l1, r1, l2, r2;
        scanf("%lld %lld %lld %lld %lld", &k, &l1, &r1, &l2, &r2);
        assert(k >= 2 && k <= 1000000000); // PRE: 2 <= k <= 10^9
        assert(l1 >= 1 && r1 >= l1 && r1 <= 1000000000); // PRE: 1 <= l1 <= r1 <= 10^9
        assert(l2 >= 1 && r2 >= l2 && r2 <= 1000000000); // PRE: 1 <= l2 <= r2 <= 10^9
        
        long long ans = 0;
        for (long long i = 1; i * l1 <= r2; i *= k) {
            long long l = (l2 + i - 1) / i > l1 ? (l2 + i - 1) / i : l1;
            long long r = r2 / i < r1 ? r2 / i : r1;
            ans += (r - l + 1 > 0) ? (r - l + 1) : 0;
        }
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: ans >= 0
    }
    return 0;
}