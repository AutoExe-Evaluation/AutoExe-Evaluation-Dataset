#include <stdio.h>
#include <assert.h>

long long power(long long x, long long y, long long m) {
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
    int n;
    long long ct = 0;
    scanf("%d", &n);
    
    assert(n >= 1 && n <= 55); // PRE: n is within the valid range [1, 55]
    
    for (int i = 1; i <= n; ++i)
        ct += power(2, i, 1000000007);
    
    printf("%lld\n", ct);
    
    assert(ct == (power(2, n + 1, 1000000007) - 2 + 1000000007) % 1000000007); // POST: ct should equal the total number of lucky numbers with unique n digits
    
    return 0;
}