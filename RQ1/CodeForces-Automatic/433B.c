#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    long long n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 100000); // PRE: n is within allowed range

    long long *v = (long long *)malloc(n * sizeof(long long));
    long long *pre = (long long *)calloc(n + 1, sizeof(long long));
    long long *pre2 = (long long *)calloc(n + 1, sizeof(long long));
    
    for (long long i = 0; i < n; ++i) {
        scanf("%lld", &v[i]);
        assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: v[i] is within allowed range
    }

    for (long long i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + v[i - 1];
    }

    // Sort the array
    for (long long i = 0; i < n - 1; ++i) {
        for (long long j = i + 1; j < n; ++j) {
            if (v[i] > v[j]) {
                long long temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }

    for (long long i = 1; i <= n; ++i) {
        pre2[i] = pre2[i - 1] + v[i - 1];
    }

    long long m;
    scanf("%lld", &m);
    assert(m >= 1 && m <= 100000); // PRE: m is within allowed range
    while (m--) {
        long long type, l, r;
        scanf("%lld %lld %lld", &type, &l, &r);
        assert(l >= 1 && r <= n && l <= r); // PRE: l, r are within allowed range
        if (type == 1)
            printf("%lld\n", pre[r] - pre[l - 1]);
        else
            printf("%lld\n", pre2[r] - pre2[l - 1]);
    }

    free(v);
    free(pre);
    free(pre2);
    
    // POST: The answers printed are correct based on the input queries
    return 0;
}