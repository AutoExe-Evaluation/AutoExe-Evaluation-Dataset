#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long
#define MAX_LEN 10

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
    ll n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 1000000000); // PRE: 1 <= n <= 10^9

    ll v[1024]; // to store up to 256 super lucky numbers
    int count = 0;

    for (int len = 2; len <= MAX_LEN; len += 2) {
        int half = len / 2;
        for (int mask = 0; mask < (1 << len); mask++) {
            if (__builtin_popcount(mask) != half) continue;

            ll num = 0;
            for (int pos = 0; pos < len; pos++) {
                num = num * 10 + ((mask & (1 << pos)) ? 4 : 7);
            }
            v[count++] = num;
        }
    }

    // Sort the array 'v'
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                ll temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        if (v[i] >= n) {
            printf("%lld\n", v[i]);
            assert(v[i] % 10 == 4 || v[i] % 10 == 7); // POST: v[i] is a lucky number
            return 0;
        }
    }
}