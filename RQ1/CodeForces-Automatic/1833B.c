#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int cmp(const void *a, const void *b) {
    return (*(pair<ll, int> *)a).first - (*(pair<ll, int> *)b).first;
}

int cmp_ll(const void *a, const void *b) {
    return *(ll *)a - *(ll *)b;
}

int main() {
    ll TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases within limits

    while (TC--) {
        ll n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 1 && n <= 100000); // PRE: number of days within limits
        assert(k >= 0 && k <= 1000000000); // PRE: maximum difference limit

        ll *a = (ll *)malloc(n * sizeof(ll));
        ll *b = (ll *)malloc(n * sizeof(ll));
        ll *c = (ll *)malloc(n * sizeof(ll));
        pair<ll, int> *pairs = (pair<ll, int> *)malloc(n * sizeof(pair<ll, int>));

        for (ll i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            pairs[i].first = a[i];
            pairs[i].second = i;
        }

        for (ll i = 0; i < n; ++i) {
            scanf("%lld", &b[i]);
        }

        qsort(pairs, n, sizeof(pair(ll, int)), cmp);
        qsort(b, n, sizeof(ll), cmp_ll);

        for (ll i = 0; i < n; ++i) {
            c[pairs[i].second] = b[i];
            assert(abs(a[pairs[i].second] - c[pairs[i].second]) <= k); // POST: temperature condition met
        }

        for (ll i = 0; i < n; ++i) {
            printf("%lld ", c[i]);
        }
        printf("\n");

        free(a);
        free(b);
        free(c);
        free(pairs);
    }
    return 0;
}