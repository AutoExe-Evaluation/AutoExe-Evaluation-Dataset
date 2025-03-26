#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long abs(long long x) {
    return x < 0 ? -x : x;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= t <= 1000
    for (int TC = 1; TC <= TCS; ++TC) {
        int n, k, p;
        scanf("%d %d %d", &n, &k, &p);

        assert(n >= 1 && n <= 50); // PRE: 1 <= n <= 50
        assert(k >= -2500 && k <= 2500); // PRE: -2500 <= k <= 2500
        assert(p >= 1 && p <= 50); // PRE: 1 <= p <= 50

        if (k > n * p || k < n * (-p)) {
            printf("-1\n");
            continue;
        }
        if (k == 0) {
            printf("0\n");
            continue;
        }

        int ct = 0;
        int r = abs(k); 
        while (r > 0) {
            if (r <= p) {
                ct++;
                break;
            }
            r -= p;
            ct++;
        }
        printf("%d\n", ct); 
        assert(ct >= 0); // POST: ct >= 0
    }
    return 0;
}