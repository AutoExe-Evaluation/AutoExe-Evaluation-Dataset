#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long abs(long long x) {
    return x < 0 ? -x : x;
}

int main() {
    int TCS;
    scanf("%d", &TCS); 
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4

    for (int TC = 1; TC <= TCS; ++TC) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 ≤ n ≤ 2 * 10^5
        long long *a = (long long *)malloc(n * sizeof(long long));
        long long *b = (long long *)malloc((n + 1) * sizeof(long long));

        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
        }
        for (long long i = 0; i < n + 1; ++i) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: 1 ≤ b_i ≤ 10^9
        }

        long long ans = 0, diff = 1e18;
        for (long long i = 0; i < n; ++i) {
            ans += abs(a[i] - b[i]);
            diff = (diff < abs(b[n] - a[i])) ? diff : abs(b[n] - a[i]);
            diff = (diff < abs(b[n] - b[i])) ? diff : abs(b[n] - b[i]);
            if (b[n] >= (a[i] < b[i] ? a[i] : b[i]) && b[n] <= (a[i] > b[i] ? a[i] : b[i])) {
                diff = 0;
            }
        }
        printf("%lld\n", ans + 1 + diff);
        free(a);
        free(b);
    }
    return 0;
} // POST: The output is the minimum number of operations required to transform array a into array b for all test cases.