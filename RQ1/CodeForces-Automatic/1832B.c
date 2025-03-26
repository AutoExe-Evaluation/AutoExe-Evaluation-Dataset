#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 200000

long long pre[MAX_N + 1];

int compare(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10000

    while (TC--) {
        long long n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 3 && n <= 200000); // PRE: 3 <= n <= 200000
        assert(k >= 1 && k <= 99999); // PRE: 1 <= k <= 99999
        assert(2 * k < n); // PRE: 2k < n
        
        long long v[MAX_N];
        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }

        qsort(v, n, sizeof(long long), compare);
        
        pre[0] = 0;
        for (long long i = 1; i <= n; ++i) {
            pre[i] = v[i - 1] + pre[i - 1];
        }
        
        long long mx = 0;
        for (long long i = 0; i <= k; ++i) {
            long long current = pre[n - i] - pre[2 * (k - i)];
            if (current > mx) {
                mx = current;
            }
        }
        printf("%lld\n", mx);
        assert(mx >= 0); // POST: Maximum possible sum should be non-negative
    }
    return 0;
}