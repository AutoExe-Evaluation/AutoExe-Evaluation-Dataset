#include <stdio.h>
#include <assert.h>

typedef long long ll;

ll lcm(ll a, ll b) {
    return (a / __gcd(a, b)) * b;
}

int main() {
    ll x, ans = 1;
    scanf("%lld", &x);
    
    assert(x >= 1 && x <= 1000000000000LL); // PRE: 1 ≤ X ≤ 10^12
    
    for (ll i = 1; i * i <= x; ++i) {
        if (x % i == 0 && lcm(i, x / i) == x) {
            ans = i;
        }
    }
    
    printf("%lld %lld\n", ans, x / ans);
    
    assert(ans > 0 && (x / ans) > 0); // POST: a, b > 0 (where a = ans, b = x / ans)
    return 0;
}