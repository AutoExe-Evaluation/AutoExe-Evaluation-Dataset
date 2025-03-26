#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (t--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 1 && n <= 200000); // PRE: 1 ≤ n ≤ 2 * 10^5
        assert(k >= 1 && k <= 200000); // PRE: 1 ≤ k ≤ 2 * 10^5
        
        int *a = (int *)malloc(n * sizeof(int));
        int *pre = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000); // PRE: 1 ≤ a_i ≤ 10^3
        }

        pre[0] = a[0];
        for (int i = 1; i < n; ++i)
            pre[i] = a[i] + pre[i - 1];

        int mx = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000); // PRE: 1 ≤ b_i ≤ 10^3
            if (mx < b[i])
                mx = b[i];
            if (i < k)
                ans = (ans > pre[i] + mx * (k - i - 1)) ? ans : (pre[i] + mx * (k - i - 1));
        }
        
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: The maximum experience should be non-negative

        free(a);
        free(pre);
        free(b);
    }
    return 0;
}