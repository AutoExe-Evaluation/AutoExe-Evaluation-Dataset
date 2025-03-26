#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int compare(const ll* a, const ll* b) {
    return (*a - *b);
}

int main() {
    ll TC;
    scanf("%lld", &TC); // PRE: TC >= 1, (n * m) <= 200000, h <= 1000000

    while (TC--) {
        ll n, m, h;
        scanf("%lld %lld %lld", &n, &m, &h);
        
        ll* solved = (ll*)malloc(n * sizeof(ll));
        ll* penalty = (ll*)malloc(n * sizeof(ll));
        ll rs, rp;

        for (ll i = 0; i < n; ++i) {
            ll* a = (ll*)malloc(m * sizeof(ll));
            assert(a != NULL); // Assert for memory allocation

            for (ll j = 0; j < m; ++j) {
                scanf("%lld", &a[j]);
            }
            qsort(a, m, sizeof(ll), (int(*)(const void*, const void*))compare);
            
            ll time = 0, pen = 0, ct = 0;
            for (ll j = 0; j < m; ++j) {
                time += a[j];
                if (h >= time) {
                    ct++;
                    pen += time;
                }
            }

            if (i == 0) {
                rs = ct;
                rp = pen;
            }
            solved[i] = ct;
            penalty[i] = pen;
            free(a);
        }

        ll pos = 1;
        for (ll i = 1; i < n; ++i) {
            if (solved[i] > rs) pos++;
            else if (solved[i] == rs) {
                if (penalty[i] < rp) pos++;
            }
        }
        printf("%lld\n", pos);
        free(solved);
        free(penalty);
    }

    return 0; // POST: Rudolf's position is printed correctly based on the optimal problem-solving order
}