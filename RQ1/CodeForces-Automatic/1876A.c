#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    long long ff;
    long long ss;
} Pair;

int cmp(const void *a, const void *b) {
    Pair *pairA = (Pair *)a;
    Pair *pairB = (Pair *)b;
    if (pairA->ff == pairB->ff) 
        return pairB->ss - pairA->ss;
    return pairA->ff - pairB->ff;
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within the limits

    while (TCS--) {
        long long n, p;
        scanf("%lld %lld", &n, &p);
        assert(n >= 1 && n <= 100000); // PRE: Number of residents is within the limits
        assert(p >= 1 && p <= 100000); // PRE: Cost for direct sharing is within the limits

        Pair *v = (Pair *)malloc(n * sizeof(Pair));
        for (long long i = 0; i < n; i++) {
            scanf("%lld", &v[i].ss);
            assert(v[i].ss >= 1 && v[i].ss <= 100000); // PRE: Shares limit is within the limits
        }
        for (long long i = 0; i < n; i++) {
            scanf("%lld", &v[i].ff);
            assert(v[i].ff >= 1 && v[i].ff <= 100000); // PRE: Cost per share is within the limits
        }
        
        qsort(v, n, sizeof(Pair), cmp);

        long long rem = n - 1, ans = p;   
        for (long long i = 0; i < n; i++) {
            if (v[i].ff >= p) break;
            long long ct = rem < v[i].ss ? rem : v[i].ss;
            ans += ct * v[i].ff;
            rem -= ct;
        }
        ans += rem * p;
        printf("%lld\n", ans);
        assert(ans >= p && ans <= 1000000000000); // POST: Total cost is within reasonable limits for all residents notified

        free(v);
    }
    return 0;
}