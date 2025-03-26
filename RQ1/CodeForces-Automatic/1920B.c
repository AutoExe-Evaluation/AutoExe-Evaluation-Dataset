#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN (-1000000000)

long long pre[200001], v[200001];

int main() {
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        long long n, k, x;
        scanf("%lld %lld %lld", &n, &k, &x);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        assert(k >= 1 && k <= n); // PRE: 1 <= k <= n
        assert(x >= 1 && x <= n); // PRE: 1 <= x <= n

        for (long long i = 1; i <= n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000); // PRE: 1 <= a_i <= 1000
        }

        qsort(v + 1, n, sizeof(long long), (__compar_fn_t)(long long(*)(const void *, const void *))(*(long long *)&y1 - *(long long *)&y2));

        for (long long i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] + v[i];

        long long ans = MIN;
        for (long long i = n; i >= n - k; --i) {
            long long r = (i < x) ? i : x;
            ans = (ans > 2 * pre[i - r] - pre[i]) ? ans : (2 * pre[i - r] - pre[i]);
        }

        printf("%lld\n", ans);
        assert(ans >= MIN); // POST: the final sum must be at least MIN
    }
    return 0;
}