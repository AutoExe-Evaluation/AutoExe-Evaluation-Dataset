#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases should be valid
    
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100000); // PRE: length of permutation should be valid
        
        int *v = (int *)malloc((n + 1) * sizeof(int));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= n); // PRE: each element of permutation should be valid
        }
        
        int ans = 0, diff;
        for (int i = 1; i <= n; ++i) {
            diff = abs(v[i] - i);
            ans = gcd(ans, diff);
        }
        
        printf("%d\n", ans);
        free(v);
        
        assert(ans >= 1 && ans <= n - 1); // POST: max k value should be in valid range
    }
    return 0;
}