#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ T ≤ 10^4
    
    while (TCS--) {
        int n, k;
        scanf("%lld%lld", &n, &k);
        assert(n >= 1 && n <= 50); // PRE: 1 ≤ n ≤ 50
        assert(k >= 1 && k <= 100); // PRE: 1 ≤ k ≤ 100
        
        int has = 0, ct = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 0 && x <= 100); // PRE: 0 ≤ a_i ≤ 100
            
            if (x >= k) {
                has += x;
            }
            if (has && x == 0) {
                ct++;
                has--;
            }
        }
        printf("%lld\n", ct);
        assert(ct >= 0 && ct <= n); // POST: Number of people getting gold is non-negative and ≤ n
    }
    return 0;
}