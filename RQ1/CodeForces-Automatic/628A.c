#include <stdio.h>
#include <math.h>
#include <assert.h>

int main() {
    long long n, b, p;
    scanf("%lld %lld %lld", &n, &b, &p);
    
    // PRE: n >= 1, b >= 1, p >= 1
    assert(n >= 1 && b >= 1 && p >= 1);

    long long towel = n * p;
    long long ct = 0;
    
    while (1) {
        if (n == 1) break; 
        long long k = (long long)log2(n);
        ct += 2 * k * b + k;
        n -= k; 
    }
    
    // POST: ct is the total number of bottles and towel is the total number of towels
    assert(ct >= 0); // ensuring bottles count is non-negative
    assert(towel >= 0); // ensuring towels count is non-negative
    
    printf("%lld %lld\n", ct, towel);
    return 0;
}