#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

ll mypow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a);
        a = (a * a);
        b >>= 1;
    }
    return ans;
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        ll a, b, l;
        scanf("%lld %lld %lld", &a, &b, &l);
        assert(a >= 2 && a <= 100); // PRE: 2 <= a <= 100
        assert(b >= 2 && b <= 100); // PRE: 2 <= b <= 100
        assert(l >= 1 && l <= 1000000); // PRE: 1 <= l <= 10^6

        int* st = (int*)malloc(1000000 * sizeof(int));
        int count = 0;

        for (ll x = 0; mypow(a, x) <= l; ++x) {
            for (ll y = 0; mypow(b, y) <= l; ++y) {
                ll res = mypow(a, x) * mypow(b, y);
                if (l % res == 0) {
                    ll k = l / res;
                    if (k < 1000000 && !st[k]) {
                        st[k] = 1;
                        count++;
                    }
                }
            }
        }

        printf("%d\n", count);
        free(st);
        assert(count >= 0); // POST: count >= 0
    }

    return 0;
}