#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef long long ll;

int main() {
    ll TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: 1 ≤ t ≤ 500

    while (TCS--) {
        ll n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 2000); // PRE: 1 ≤ n ≤ 2000

        ll* v = (ll*)malloc(n * sizeof(ll));
        for (ll i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] > 0 && v[i] < 1e18); // PRE: 0 < a_i < 10^18
            if (i > 0) assert(v[i-1] < v[i]); // PRE: a_i < a_{i + 1}
        }

        ll ans;
        if (n == 1) {
            ans = 1;
        } else if (n % 2) {
            ans = 1e18;
            for (ll i = 0; i < n; ++i) {
                ll* temp = (ll*)malloc((n - 1) * sizeof(ll));
                for (ll j = 0, index = 0; j < n; ++j) {
                    if (i == j) continue;
                    temp[index++] = v[j];
                }

                ll mx = 0;
                for (ll j = 1; j < n - 1; j += 2) {
                    mx = mx > temp[j] - temp[j - 1] ? mx : temp[j] - temp[j - 1];
                }
                ans = ans < mx ? ans : mx;
                free(temp);
            }
        } else {
            ll mx = 0;
            for (ll i = 1; i < n; i += 2) {
                mx = mx > v[i] - v[i - 1] ? mx : v[i] - v[i - 1];
            }
            ans = mx;
        }    

        printf("%lld\n", ans);
        assert(ans >= 0); // POST: The output should be a valid non-negative minimum value of k
        free(v);
    }
    return 0;
}