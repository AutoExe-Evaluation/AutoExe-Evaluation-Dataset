#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within bounds

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: Number of elements is within bounds

        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= n); // PRE: Each element of permutation is within bounds
        }

        char *s = (char *)malloc(n * sizeof(char));
        scanf("%s", s);
        long long *ans = (long long *)calloc(n, sizeof(long long));
        int *vis = (int *)calloc(n, sizeof(int));

        for (int i = 0; i < n; ++i) {
            long long ct = 0;
            // Definition of the recursive function inline to avoid multiple main functions
            void fn(int *v, char *s, long long *ans, int *vis, long long *ct, int i) {
                if (vis[i]) return;
                if (s[i] == '0') (*ct)++;
                vis[i] = 1;
                fn(v, s, ans, vis, ct, v[i] - 1);
                ans[i] = *ct;
            }
            fn(v, s, ans, vis, &ct, i);
        }

        for (int i = 0; i < n; ++i) {
            printf("%lld ", ans[i]);
        }
        printf("\n");

        free(v);
        free(s);
        free(ans);
        free(vis);
    }

    return 0;
    // POST: The output is valid and aligns with the problem constraints
}