#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000

    while (TC--) {
        int x, y, n;
        scanf("%lld %lld %lld", &x, &y, &n);
        assert(1 <= x && x < y && y <= 1000); // PRE: 1 <= x < y <= 1000
        assert(3 <= n && n <= 1000); // PRE: 3 <= n <= 1000
        
        int *a = (int *)malloc(n * sizeof(int));
        if (n * (n - 1) > 2 * (y - x)) {
            printf("-1\n"); // Impossible case, return -1
        } else {
            int ct = 0;
            a[ct++] = x;
            for (int i = 1; ct < n - 1; ++i) {
                a[ct++] = y - i;
            }
            a[ct++] = y;

            for (int i = 0; i < n; i++) {
                printf("%lld ", a[i]);
            }
            printf("\n");
        }
        free(a);
    }
    return 0;
} // POST: The output array a satisfies a_1=x, a_n=y; a is strictly increasing and b is strictly decreasing if not -1.