#include <stdio.h>
#include <math.h>
#include <assert.h>

#define ull unsigned long long

int main() {
    int t;
    scanf("%d", &t);
    assert(t >= 1 && t <= 10000); // PRE: 1 <= t <= 10000

    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 200000
        assert(k >= 1 && k <= 1000000000); // PRE: 1 <= k <= 10^9
        
        if (n == 1) {
            printf("%d\n", k);
            assert(k >= 0); // POST: a_1 = k >= 0
            continue;
        }
        if (k == 1) {
            for (int i = 0; i < n - 1; ++i)
                printf("0 ");
            printf("1\n");
            assert((1 & 1) == 1); // POST: At least one 1 in the OR
            continue;
        }
        int x = log2(k);
        x--;
        int r = (2 << x) - 1;
        for (int i = 0; i < n - 2; ++i)
            printf("0 ");
        printf("%d %d\n", r, k - r);
        assert((r | (k - r)) == k); // POST: The sum is k
    }
    
    return 0;
}