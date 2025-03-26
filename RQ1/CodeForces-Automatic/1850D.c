#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 200000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= TC <= 1000
    while (TC--) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 200000
        assert(k >= 1 && k <= 1000000000); // PRE: 1 <= k <= 10^9

        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }

        qsort(v, n, sizeof(int), compare);

        int mx = 0, ct = 1;
        for (int i = 1; i < n; i++) {
            int d = v[i] - v[i - 1];
            if (d <= k) {
                ct++;
            } else {
                if (mx < ct) mx = ct;
                ct = 1;
            }
        }
        if (mx < ct) mx = ct;

        printf("%d\n", n - mx);
        free(v);
        assert(n - mx >= 0); // POST: The number of removed problems is non-negative
    }
    return 0;
}