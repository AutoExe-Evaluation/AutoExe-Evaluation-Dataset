#include <stdio.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4

    while (TCS--) {
        long long n, l, r;
        scanf("%lld%lld%lld", &n, &l, &r);
        assert(n >= 1 && n <= 100000); // PRE: 1 <= n <= 10^5
        assert(l >= 1 && l <= r && r <= 1000000000); // PRE: 1 <= l <= r <= 10^9
        
        long long v[100000];
        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }
        
        long long sum = 0, ans = 0, i = 0;
        for (long long j = 0; j < n; ++j) {
            sum += v[j];
            while (i <= j && sum > r) {
                sum -= v[i];
                i++;
            }
            if (sum >= l && sum <= r) {
                ans++;
                sum = 0;
                i = j + 1;
            }
        }
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: Maximum number of rounds Egor can win is non-negative
    }
    return 0;
}