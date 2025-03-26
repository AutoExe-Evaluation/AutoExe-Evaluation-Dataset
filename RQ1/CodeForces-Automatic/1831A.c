#include <stdio.h>
#include <assert.h>

#define MAX_N 100

int main() {
    long long t, n, x;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 2000); // PRE: Number of test cases is within allowed range
    while (t--) {
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: Length of permutation is within allowed range
        long long ans[MAX_N];
        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &x);
            assert(x >= 1 && x <= n); // PRE: Each element is within the bounds of permutation
            ans[i] = n + 1 - x;
        }
        for (long long i = 0; i < n; ++i) {
            printf("%lld ", ans[i]);
            assert(ans[i] >= 1 && ans[i] <= n); // POST: Ensuring output is valid for permutation
        }
        printf("\n");
    }
    return 0;
}