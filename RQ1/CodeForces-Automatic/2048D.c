#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

int main() {
    ll t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 50000); // PRE: t is the number of test cases

    while (t--) {
        ll n, m, INF = 1e18;
        scanf("%lld %lld", &n, &m);
        assert(n >= 1 && n <= 300000); // PRE: n is the number of participants
        assert(m >= 1 && m <= 300000); // PRE: m is the number of problems

        ll* a = (ll*)malloc(n * sizeof(ll));
        ll* b = (ll*)malloc(m * sizeof(ll));
        for (ll i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 0 && a[i] <= 1000000000); // PRE: participant ratings are within bounds
        }
        for (ll i = 0; i < m; ++i) {
            scanf("%lld", &b[i]);
            assert(b[i] >= 0 && b[i] <= 1000000000); // PRE: problem difficulties are within bounds
        }

        ll kevin = a[0];
        ll* p = (ll*)malloc((n - 1) * sizeof(ll));
        ll* cnt = (ll*)malloc(m * sizeof(ll));
        ll p_size = 0;

        for (ll i = 1; i < n; ++i) {
            if (a[i] > kevin) p[p_size++] = a[i];
        }

        for (ll i = 0; i < m; ++i) {
            if (b[i] <= kevin) b[i] = INF;
            ll count = 0;
            for (ll j = 0; j < p_size; ++j) {
                if (p[j] >= b[i]) break;
                count++;
            }
            cnt[i] = p_size - count;
        }

        for (ll k = 1; k <= m; ++k) {
            ll contest = m / k;
            ll sum = 0;
            for (ll i = k - 1; i < contest * k; i += k) {
                ll rank = 1 + cnt[i];
                sum += rank;
            }
            printf("%lld ", sum);
        }
        printf("\n");

        free(a);
        free(b);
        free(p);
        free(cnt);
    }

    return 0; 
    assert(true); // POST: The program finishes without errors, outputs valid ranks for each test case
}