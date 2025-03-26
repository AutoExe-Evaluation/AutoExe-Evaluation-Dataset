#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= t <= 1000

    for (int TC = 1; TC <= TCS; ++TC) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 1 && n <= 1000); // PRE: 1 <= n <= 1000
        assert(k >= 2 && k <= 1000); // PRE: 2 <= k <= 1000

        int ct = 0;
        while (n > 1) {
            n -= (k - 1);
            ct++;
        }
        assert(ct >= 0); // POST: ct is non-negative
        printf("%d\n", ct);
    }

    return 0;
}