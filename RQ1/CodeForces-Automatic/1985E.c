#include <stdio.h>
#include <assert.h>

typedef long long ll;

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
    assert(TCS >= 1 && TCS <= 2000); // PRE: TCS is within bounds

    for (int TC = 1; TC <= TCS; ++TC) {
        ll x, y, z, k;
        scanf("%lld %lld %lld %lld", &x, &y, &z, &k);
        assert(x >= 1 && x <= 2000); // PRE: x is within bounds
        assert(y >= 1 && y <= 2000); // PRE: y is within bounds
        assert(z >= 1 && z <= 2000); // PRE: z is within bounds
        assert(k >= 1 && k <= x * y * z); // PRE: k is within bounds
        
        ll mx = 0;
        for (ll a = 1; a <= x; ++a) {
            for (ll b = 1; b <= y; ++b) {
                if (k % (a * b)) continue;
                ll c = k / (a * b);
                if (c <= z && a * b * c == k) {
                    ll ct = (x - a + 1) * (y - b + 1) * (z - c + 1);
                    if (ct > mx) mx = ct;
                }
            }
        }
        
        assert(mx >= 0); // POST: mx is non-negative
        printf("%lld\n", mx);
    }
    
    return 0;
}