#include <stdio.h>
#include <assert.h>

#define ll long long
#define MOD 1000000007

ll pow(ll x, ll y, ll m) {
    ll ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within bounds.
    
    while (TCS--) {
        ll l, r, k;
        scanf("%lld %lld %lld", &l, &r, &k);
        assert(0 <= l && l < r && r <= 1000000000); // PRE: l and r should be in the provided range.
        assert(1 <= k && k <= 1000000000); // PRE: k should be within bounds.

        if (k > 9) {
            printf("0\n");
            continue;
        }
        
        ll ct1 = pow(9 / k + 1, r, MOD);
        ll ct2 = pow(9 / k + 1, l, MOD);
        ll ans = (ct1 - ct2 + MOD) % MOD;

        printf("%lld\n", ans);
        assert(ans >= 0); // POST: The answer should be non-negative.
    }
    return 0;
}