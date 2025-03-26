#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 <= t <= 100
    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 100); // PRE: 2 <= n <= 100

        int *v = (int *)malloc(2 * n * sizeof(int));
        for (int i = 0; i < 2 * n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 0 && v[i] <= 1000); // PRE: 0 <= a_i <= 1000
        }

        qsort(v, 2 * n, sizeof(int), cmp);
        
        int x = 0, y = 0;
        for (int i = 1; i < n; ++i)
            x += v[i - 1] - v[i];
        for (int i = n + 1; i < 2 * n; ++i)
            y += v[i - 1] - v[i];
        
        printf("%lld\n", x + y); // Output the minimum path length
        for (int i = 0; i < n; ++i)
            printf("%lld %lld\n", v[i], v[n + i]); // Output the points

        free(v);
    }
    // POST: The output represents n points and minimum path length is calculated correctly.
    return 0;
}