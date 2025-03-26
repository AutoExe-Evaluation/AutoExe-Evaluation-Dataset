#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXN 100

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 5000); // PRE: 1 <= t <= 5000
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: 1 <= n <= 50
        n = 2 * n;
        int v[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 10000000); // PRE: 1 <= a_i <= 10^7
        }
        int ans = 0;

        qsort(v, n, sizeof(int), compare); // Using qsort for sorting

        for (int i = 1; i < n; i += 2) {
            ans += (v[i] < v[i - 1]) ? v[i] : v[i - 1];
        }
        printf("%d\n", ans);
        assert(ans >= 0); // POST: Score should be a non-negative integer
    }
    return 0;
}