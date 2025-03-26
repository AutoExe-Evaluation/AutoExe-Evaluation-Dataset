#include <stdio.h>
#include <assert.h>

long long pow(long long x, long long y, long long m) {
    long long ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int main() {
    long long TCS = 1;
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4
    scanf("%lld", &TCS);
  
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n, k;
        scanf("%lld %lld", &n, &k);
        
        assert(n >= 1 && n <= 1000000000); // PRE: 1 <= n <= 10^9
        assert(k >= 1 && k <= 1000000000); // PRE: 1 <= k <= 10^9
        
        long long ct = 0;
        
        if (k == 1) {
            printf("%lld\n", n);
            assert(ct == n); // POST: ct equals n when k is 1
            continue;
        }
        
        if (n < k) {
            printf("%lld\n", n);
            assert(ct == n); // POST: ct equals n when n < k
            continue;
        }

        while (n > 0) {
            ct += (n % k);
            n /= k;
        }
        
        printf("%lld\n", ct);
        assert(ct >= 0); // POST: ct is non-negative, as it counts operations
    }
    return 0;
}