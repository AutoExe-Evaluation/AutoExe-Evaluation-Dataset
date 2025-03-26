#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    long long t;
    scanf("%lld", &t); // PRE: t should be >= 1 and <= 1000.
    assert(t >= 1 && t <= 1000); // POST: Number of test cases is within limits.

    while (t--) {
        long long n, k;
        scanf("%lld %lld", &n, &k); // PRE: n should be >= 2 and <= 50; k should be >= 0 and <= n - 1.
        assert(n >= 2 && n <= 50 && k >= 0 && k <= n - 1); // POST: Inputs n and k are valid.

        long long *v = (long long *)malloc(n * sizeof(long long));
        
        for (long long i = n - 1; i >= 0; --i) {
            v[n - i - 1] = i + 1;
        }
        
        for (long long i = 0; i <= k; ++i) {
            for (long long j = i + 1; j <= k; ++j) {
                if (v[i] > v[j]) {
                    long long temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
                }
            }
        }

        for (long long i = 0; i < n; ++i) {
            printf("%lld ", v[i]);
        }
        printf("\n");
        
        free(v);
    }
    
    return 0;
}