#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within limits
    while (TCS--) {
        long long n, a, b;
        scanf("%lld %lld %lld", &n, &a, &b);
        assert(n >= 1 && n <= 100000); // PRE: Length of the array is within limits
        assert(a >= 1 && a <= 1000000000); // PRE: a is within limits
        assert(b >= 1 && b <= 1000000000); // PRE: b is within limits
        
        long long g = gcd(a, b);
        long long *c = (long long *)malloc(n * sizeof(long long));
        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &c[i]);
            assert(c[i] >= 1 && c[i] <= 1000000000); // PRE: Each element in array c is within limits
            c[i] %= g;
        }
        
        qsort(c, n, sizeof(long long), (__compar_fn_t)long long);
        long long ans = c[n - 1] - c[0];
        for (int i = 1; i < n; ++i) {
            long long diff = c[i - 1] + g - c[i];
            if (diff < ans) ans = diff;
        }
        
        printf("%lld\n", ans);
        free(c);
    }
    assert(TCS == 0); // POST: All test cases processed
    return 0;
}