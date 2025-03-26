#include <stdio.h>
#include <limits.h>
#include <assert.h>

int main() {
    long long n, l, r, x;
    scanf("%lld %lld %lld %lld", &n, &l, &r, &x);
    assert(n >= 1 && n <= 15); // PRE: 1 ≤ n ≤ 15
    assert(l <= r && l >= 1 && r <= 1e9); // PRE: 1 ≤ l ≤ r ≤ 10^9
    assert(x >= 1 && x <= 1e6); // PRE: 1 ≤ x ≤ 10^6
    long long prob[15];
    for (long long i = 0; i < n; ++i) {
        scanf("%lld", &prob[i]);
        assert(prob[i] >= 1 && prob[i] <= 1e6); // PRE: 1 ≤ ci ≤ 10^6
    }

    long long ans = 0;
    for (long long mask = 0; mask < (1 << n); mask++) {
        long long ct = 0, sum = 0, mx = 0, mn = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                ct++;
                sum += prob[i];
                if (prob[i] < mn) mn = prob[i];
                if (prob[i] > mx) mx = prob[i];
            }
        }
        if (ct >= 2 && sum >= l && sum <= r && mx - mn >= x) ans++;
    }
    printf("%lld\n", ans);
    assert(ans >= 0); // POST: Number of ways to choose a problemset is non-negative
    return 0;
}