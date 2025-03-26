#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within the bounds

    while (TCS--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Array length must satisfy constraints
        bool even = false, odd = false;

        for (long long i = 0; i < n; ++i) {
            long long x;
            scanf("%lld", &x);
            assert(x >= 0 && x <= 1000000000); // PRE: Array elements must be within bounds
            if (x & 1)
                odd = true;
            else 
                even = true;
        }
        
        // Check for impossible case
        if (even && odd) {
            printf("-1\n");
            continue;
        }
        
        long long ans[40];
        long long size = 0;

        for (long long i = 29; i >= 0; --i) {
            ans[size++] = 1LL << i;
        }
        if (even) {
            ans[size++] = 1;
        }

        assert(size <= 40); // POST: Number of operations should not exceed 40
        printf("%lld\n", size);
        for (long long i = 0; i < size; ++i) {
            printf("%lld ", ans[i]);
        }
        printf("\n");
    }
    
    return 0;
}