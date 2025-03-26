#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

int compare(const void* a, const void* b) {
    return (*(long long*)a - *(long long*)b);
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within limits.

    while (TCS--) {
        long long n, m;
        scanf("%lld %lld", &n, &m);
        assert(n >= 1 && n <= 200000); // PRE: Number of elements in array a should be within limits.
        assert(m >= 1 && m <= 200000); // PRE: Number of elements in array b should be within limits.

        long long* a = (long long*)malloc(n * sizeof(long long));
        long long* b = (long long*)malloc(m * sizeof(long long));
        
        for (long long i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000000); // PRE: Elements of array a should be within limits.
        }
        for (long long i = 0; i < m; i++) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000000); // PRE: Elements of array b should be within limits.
        }
        
        qsort(b, m, sizeof(long long), compare);
        
        long long dp = -1e18;
        bool ok = true;
        
        for (long long i = 0; i < n; i++) {
            long long mx = LLONG_MAX;
            if (a[i] >= dp) {
                mx = a[i] < mx ? a[i] : mx;
            }
            
            long long need = dp + a[i];
            long long* it = (long long*)bsearch(&need, b, m, sizeof(long long), compare);
            if (it != NULL) {
                long long x = *it - a[i];
                if (x >= dp) {
                    mx = x < mx ? x : mx;
                }
            }
            
            if (mx == LLONG_MAX) {
                ok = false;
                break;
            }
            dp = mx;
        }
        
        printf(ok ? "YES\n" : "NO\n");
        assert(ok ? dp >= 0 : dp < 0); // POST: If "YES", dp should be non-negative; if "NO", it should be negative.
        free(a);
        free(b);
    }
}