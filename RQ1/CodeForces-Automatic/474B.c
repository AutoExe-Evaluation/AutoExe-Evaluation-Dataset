#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    long long n, last = 1;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5

    long long *a = (long long *)malloc(n * sizeof(long long));
    long long total_worms = 0;

    for (long long i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
        total_worms += a[i];
        assert(a[i] >= 1 && a[i] <= 1000); // PRE: 1 ≤ ai ≤ 10^3
    }

    assert(total_worms <= 1000000); // PRE: a1 + a2 + ... + an ≤ 10^6

    long long *v = (long long *)malloc((total_worms + 1) * sizeof(long long));

    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < a[i]; ++j, last++) {
            v[last] = i + 1;
        }
    }

    long long q;
    scanf("%lld", &q);
    assert(q >= 1 && q <= 100000); // PRE: 1 ≤ m ≤ 10^5

    while (q--) {
        long long x;
        scanf("%lld", &x);
        assert(x >= 1 && x <= total_worms); // PRE: 1 ≤ qi ≤ a1 + a2 + ... + an
        printf("%lld\n", v[x]);
    }
    
    free(a);
    free(v);
    assert(1 <= total_worms); // POST: The output corresponds to the correct pile numbers for given juicy worm labels.

    return 0;
}