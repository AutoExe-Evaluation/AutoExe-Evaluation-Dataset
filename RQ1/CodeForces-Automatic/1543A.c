#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long abs(long long x) {
    return x < 0 ? -x : x;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 5000); // PRE: 1 ≤ t ≤ 5000
    
    while (TCS--) {
        long long x, y;
        scanf("%lld%lld", &x, &y);
        assert(x >= 0 && x <= 1000000000000000000); // PRE: 0 ≤ a ≤ 10^18
        assert(y >= 0 && y <= 1000000000000000000); // PRE: 0 ≤ b ≤ 10^18

        long long ans = 0, ct = 0;
        if (x != y) {
            ans = abs(x - y);
            ct = (x % ans < ans - x % ans) ? x % ans : ans - x % ans;
        }
        
        assert(ans >= 0); // POST: maximum excitement (gcd) should be non-negative
        printf("%lld %lld\n", ans, ct);
    }
    return 0;
}