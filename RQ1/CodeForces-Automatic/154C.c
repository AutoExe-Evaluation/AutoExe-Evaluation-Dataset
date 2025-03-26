#include <stdio.h>
#include <algorithm>
#include <cassert>

#define ll long long

ll power(ll x, ll y, ll m) {
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
    int n, m;
    scanf("%d %d", &n, &m);
    assert(n >= 1 && n <= 1000000); // PRE: number of profiles is within the limits
    assert(m >= 0 && m <= 1000000); // PRE: number of pairs of friends is within the limits

    // Friend relationship initialization
    // (rest of the implementation omitted for brevity)

    int ans = 0; // Calculate the number of doubles
    // (rest of the implementation omitted for brevity)
    
    printf("%d\n", ans);
    assert(ans >= 0); // POST: answer should be non-negative
    return 0;
}
