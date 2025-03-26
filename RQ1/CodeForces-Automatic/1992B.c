#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compare(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}

void solve() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    assert(n >= 2 && k >= 2); // PRE: n >= 2, k >= 2
    long long *v = (long long *)malloc(k * sizeof(long long));
    for (long long i = 0; i < k; ++i) {
        scanf("%lld", &v[i]);
        assert(v[i] >= 1 && v[i] <= n - 1); // PRE: 1 <= a_i <= n-1
    }
    qsort(v, k, sizeof(long long), compare);
    long long ans = 0;
    for (long long i = 0; i < k - 1; ++i) {
        ans += 2 * v[i] - 1;
    }
    printf("%lld\n", ans);
    free(v);
    assert(ans >= 0); // POST: ans >= 0 (no negative operations)
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4
    for (long long TC = 1; TC <= TCS; ++TC) {
        solve();
    }
    return 0;
}