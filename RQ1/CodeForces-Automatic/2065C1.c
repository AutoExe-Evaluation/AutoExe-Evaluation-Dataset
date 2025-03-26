#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4

    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n, m = 1;
        scanf("%lld %lld", &n, &m);
        
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5

        long long *a = malloc(n * sizeof(long long));
        long long *b = malloc(m * sizeof(long long));
        
        for (long long i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: 1 <= a_i <= 10^9
        }
        
        for (long long i = 0; i < m; i++) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: 1 <= b_i <= 10^9
        }

        long long dp = -1e18;
        int ok = 1;
        
        long long need, mx;
        for (long long i = 0; i < n; i++) {
            mx = LLONG_MAX;
            if (a[i] >= dp) {
                mx = a[i];
            }

            need = dp + a[i];
            if (need <= b[0]) {
                long long x = b[0] - a[i];
                if (x >= dp) {
                    mx = (mx < x) ? mx : x;
                }
            }
            
            if (mx == LLONG_MAX) {
                ok = 0;
                break;
            }
            dp = mx;
        }
        
        printf(ok ? "YES\n" : "NO\n");
        
        free(a);
        free(b);
        
        assert(ok == 1 || ok == 0); // POST: ok should be either 1 (YES) or 0 (NO)
    }
    
    return 0;
}