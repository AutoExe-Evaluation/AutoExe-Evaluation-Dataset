#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within the limits.
    
    while (TC--) {
        ll n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 1 && n <= 200000); // PRE: Number of ships is within the limits.
        assert(k >= 1 && k <= 1000000000000000LL); // PRE: Number of attacks is within the limits.

        ll *d = (ll *)malloc(n * sizeof(ll));
        for (ll i = 0; i < n; ++i) {
            scanf("%lld", &d[i]);
            assert(d[i] >= 1 && d[i] <= 1000000000); // PRE: Durability of ships is within the limits.
        }
        
        int f = 1, ans = 0, front = 0, back = n - 1;

        while (k > 0 && front <= back) {
            if (front == back) {
                if (d[front] <= k) {
                    ans++;
                }
                break;
            }
            
            ll x = d[front];
            ll y = d[back];
            ll z = (x < y) ? x : y;

            if (f) {
                if (z == x) {
                    if (k < 2 * z - 1) break;
                    k -= 2 * z - 1;
                    y -= z - 1;
                    f = 0;
                    back--;
                    d[back + 1] = y;
                    ans++;
                } else {
                    if (k < 2 * z) break;
                    k -= 2 * z;
                    x -= z;
                    d[front] = x;
                    ans++;
                    front++;
                }
            } else {
                if (z == y) {
                    if (k < 2 * z - 1) break;
                    k -= 2 * z - 1;
                    x -= z - 1;
                    f = 1;
                    front++;
                    d[front - 1] = x;
                    ans++;
                } else {
                    if (k < 2 * z) break;
                    k -= 2 * z;
                    y -= z;
                    d[back] = y;
                    ans++;
                    back--;
                }
            }
        }
        printf("%d\n", ans);
        free(d);
    }
    assert(ans >= 0); // POST: Number of ships sunk should be non-negative.
    return 0;
}