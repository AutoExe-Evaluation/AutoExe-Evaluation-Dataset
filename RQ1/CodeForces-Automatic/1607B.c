#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4
    
    while (TCS--) {
        long long x, n;
        scanf("%lld %lld", &x, &n);
        assert(x >= -100000000000000 && x <= 100000000000000); // PRE: -10^14 <= x_0 <= 10^14
        assert(n >= 0 && n <= 100000000000000); // PRE: 0 <= n <= 10^14
        
        int m = x & 1 ? 1 : -1;
        if (n % 4 == 1) x += m * n;
        else if (n % 4 == 2) x -= m;
        else if (n % 4 == 3) x -= m * (n + 1);
        
        printf("%lld\n", x);
        assert((n % 4 == 0 && x == x) || // POST: conditions based on the pattern of jumps
               (n % 4 == 1 && x == (x + m * n)) ||
               (n % 4 == 2 && x == (x - m)) ||
               (n % 4 == 3 && x == (x - m * (n + 1))));        
    }
    return 0;
}