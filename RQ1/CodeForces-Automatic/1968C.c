#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases

    while (TCS--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 500); // PRE: Number of elements in a
        
        long long *v = (long long *)malloc((n - 1) * sizeof(long long));
        long long *ans = (long long *)malloc(n * sizeof(long long));
        
        for (long long i = 0; i < n - 1; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 500); // PRE: Elements of x
        }
        
        ans[0] = v[n - 2];
        ans[1] = 1000000000;
        
        for (long long i = n - 3; i >= 0; --i) {
            ans[n - 1 - i] = ans[n - 2 - i] - v[i];
        }
        
        // Ensure all conditions for a_i are met
        for (long long i = 0; i < n; ++i) {
            assert(ans[i] >= 1 && ans[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }
        
        for (long long i = 2; i <= n; ++i) {
            assert(v[n - i] == ans[n - i] % ans[n - i + 1]); // POST: x_i = a_i mod a_{i-1}
        }

        for (long long i = 0; i < n; ++i) {
            printf("%lld ", ans[i]);
        }
        printf("\n");
        
        free(v);
        free(ans);
    }
    
    return 0;
}