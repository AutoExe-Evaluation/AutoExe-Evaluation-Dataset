#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases is within valid bounds
    
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        assert(a >= 1 && a <= 1000000000); // PRE: Alice's coins are within valid bounds
        assert(b >= 1 && b <= 1000000000); // PRE: Minimum required coins are within valid bounds
        
        long long result;
        if (a >= b) {
            result = a;
        } else {
            long long x = (b - a);
            result = max(a - x, 0LL);
        }
        printf("%lld\n", result);
        assert(result >= 0 && result <= a); // POST: result is within the valid range
    }

    return 0;
}