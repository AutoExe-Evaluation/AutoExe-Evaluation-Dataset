#include <stdio.h>
#include <assert.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    long long n;
    scanf("%lld", &n);
    
    assert(n >= 3 && n <= 1000); // PRE: n is within the bounds [3, 1000]
    
    for (long long i = n / 2; i > 0; i--) {
        if (gcd(i, n - i) == 1) {
            printf("%lld %lld\n", i, n - i);
            assert(i < (n - i)); // POST: numerator must be less than denominator
            assert(gcd(i, n - i) == 1); // POST: fraction must be irreducible
            return 0;
        }
    }
    
    return 0;
}