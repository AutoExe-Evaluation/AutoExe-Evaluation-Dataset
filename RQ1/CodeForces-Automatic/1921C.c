#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 200000

int main() {
    long long TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be within limits

    while (TC--) {
        long long n, f, a, b;
        scanf("%lld%lld%lld%lld", &n, &f, &a, &b);
        assert(n >= 1 && n <= 200000); // PRE: Number of messages should be within limits
        assert(f >= 1 && a >= 1 && b >= 1 && f <= 1000000000 && a <= 1000000000 && b <= 1000000000); // PRE: Charge and consumption limits
        
        long long *v = (long long *)malloc((n + 1) * sizeof(long long));
        for (long long i = 1; i <= n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] > 0 && v[i] <= 1000000000); // PRE: Moments should be within limits
        }
        v[0] = 0;

        for (long long i = 1; i <= n; i++) {
            long long x = (v[i] - v[i - 1]) * a;
            f -= (x < b) ? x : b;
            if (f <= 0) {
                printf("NO\n");
                free(v);
                return 0;
            }
        }
        printf("YES\n");
        free(v);
    }
    return 0;
    // POST: The output is "YES" if all messages can be sent or "NO" otherwise.
}