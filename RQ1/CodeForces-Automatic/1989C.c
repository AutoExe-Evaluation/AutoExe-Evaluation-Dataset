#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within limits

    while (TCS--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Number of viewers should be within limits

        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= -1 && a[i] <= 1); // PRE: Attitude should be in range [-1, 1]
        }
        for (int i = 0; i < n; i++) {
            scanf("%lld", &b[i]);
            assert(b[i] >= -1 && b[i] <= 1); // PRE: Attitude should be in range [-1, 1]
        }

        int p = 0, m = 0, x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1 && b[i] == 1) p++;
            else if (a[i] == -1 && b[i] == -1) m++;
            else if (a[i] > b[i]) x += a[i];
            else if (a[i] <= b[i]) y += b[i];
        }

        while (p--) {
            if (x > y) y++;
            else x++;
        }
        while (m--) {
            if (x > y) x--;
            else y--;
        }

        int result = (x < y) ? x : y;
        printf("%lld\n", result);
        assert(result >= 0); // POST: Maximum possible rating cannot be negative

        free(a);
        free(b);
    }
    return 0;
}