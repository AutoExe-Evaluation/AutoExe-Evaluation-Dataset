#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4
    while (TC--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(k >= 1 && k <= n); // PRE: 1 <= k <= n
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= n); // PRE: 1 <= c_i <= n
        }

        if (v[0] == v[n - 1]) {
            int ct = 0;
            for (int i = 0; i < n; ++i)
                if (v[i] == v[0]) ct++;
            if (ct < k)
                printf("NO\n");
            else
                printf("YES\n");
        } else {
            int ctx = 0, cty = 0, x = n, y = 0;
            for (int i = n - 1; i >= 0; --i) {
                if (v[i] == v[n - 1])
                    cty++;
                if (cty == k) {
                    y = i;
                    break;
                }
            }
            for (int i = 0; i < n; ++i) {
                if (v[i] == v[0])
                    ctx++;
                if (ctx == k) {
                    x = i;
                    break;
                }
            }
            if (x < y)
                printf("YES\n");
            else
                printf("NO\n");
        }
        free(v);
    }
    return 0;
} // POST: Possible paths of length p satisfying the conditions have been evaluated.