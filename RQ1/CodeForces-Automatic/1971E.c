#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

ll lower_bound(ll* arr, ll size, ll key) {
    ll low = 0, high = size;
    while (low < high) {
        ll mid = low + (high - low) / 2;
        if (arr[mid] < key) low = mid + 1;
        else high = mid;
    }
    return low;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TCS--) {
        ll n, k, q;
        scanf("%lld %lld %lld", &n, &k, &q);
        assert(k <= n && n <= 1000000000); // PRE: k ≤ n ≤ 10^9
        assert(k >= 1 && q >= 1 && q <= 100000); // PRE: 1 ≤ k, q ≤ 10^5

        ll* a = (ll*)malloc((k + 1) * sizeof(ll));
        ll* b = (ll*)malloc((k + 1) * sizeof(ll));
        a[0] = b[0] = 0;

        for (ll i = 1; i <= k; ++i) {
            scanf("%lld", &a[i]);
            assert(a[i] > a[i - 1] && a[i] <= n); // PRE: a_i < a_{i+1}, 1 ≤ a_i ≤ n
        }
        
        for (ll i = 1; i <= k; ++i) {
            scanf("%lld", &b[i]);
            assert(b[i] > b[i - 1]); // PRE: b_i < b_{i+1}
        }

        while (q--) {
            ll d;
            scanf("%lld", &d);
            assert(d >= 0 && d <= n); // PRE: 0 ≤ d ≤ n
            ll ind = lower_bound(a, k + 1, d);
            if (a[ind] == d) {
                printf("%lld ", b[ind]);
            } else {
                ll dist = a[ind] - a[ind - 1];
                ll time = b[ind] - b[ind - 1];
                ll x = d - a[ind - 1];
                printf("%lld ", (x * time) / dist + b[ind - 1]);
            }
        }
        printf("\n");
        free(a);
        free(b);
    }

    return 0;
} // POST: Output for each query is the correct number of minutes passed until the car reaches point d.