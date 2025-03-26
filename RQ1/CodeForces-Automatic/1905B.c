#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);

    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be within bounds

    while (TC--) {
        int n;
        scanf("%lld", &n);
        
        assert(n >= 2 && n <= 100000); // PRE: Number of vertices should be within bounds
        
        int *m = (int *)calloc(n + 1, sizeof(int));
        
        for (int i = 0; i < n - 1; ++i) {
            int x, y;
            scanf("%lld %lld", &x, &y);
            m[x]++;
            m[y]++;
        }
        
        int ct = 0;
        for (int i = 1; i <= n; i++) {
            if (m[i] == 1) {
                ct++;
            }
        }
        
        if (ct % 2 != 0) {
            ct++;
        }
        
        printf("%lld\n", ct / 2);

        assert(ct / 2 <= (n - 1)); // POST: Minimum operations are valid with respect to edges

        free(m);
    }
    
    return 0;
}