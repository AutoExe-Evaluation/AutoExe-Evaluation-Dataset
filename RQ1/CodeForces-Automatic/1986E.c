#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define int long long

void solve() {
    int n, k;
    scanf("%lld %lld", &n, &k);
    
    assert(n >= 1 && n <= 100000); // PRE: n is in valid range
    assert(k >= 1 && k <= 1000000000); // PRE: k is in valid range

    int *m[2] = {malloc(n * sizeof(int)), malloc(n * sizeof(int))}; 
    int count[2] = {0}; // For odd/even counts
    int current = 0;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%lld", &x);
        int mod = x % k;
        m[mod][count[mod]++] = x / k; 
    }

    int odd = n & 1, ans = 0;
    for (int j = 0; j < 2; j++) {
        if (count[j] > 0) {
            int len = count[j];
            qsort(m[j], len, sizeof(int), cmpfunc);

            if (len & 1) {
                if (!odd) {
                    printf("-1\n");
                    free(m[0]);
                    free(m[1]);
                    return;
                }
                odd--;
                if (len == 1) continue;

                int *pf = (int *)calloc(len, sizeof(int));
                int *sf = (int *)calloc(len, sizeof(int));
                pf[1] = m[j][1] - m[j][0];
                sf[len - 2] = m[j][len - 1] - m[j][len - 2];

                for (int i = 3; i < len; i += 2) pf[i] = pf[i - 2] + m[j][i] - m[j][i - 1];
                for (int i = len - 4; i >= 0; i -= 2) sf[i] = sf[i + 2] + m[j][i + 1] - m[j][i];

                int mn = INT_MAX;
                for (int i = 0; i < len; i += 2) {
                    int sum = 0;
                    if (i > 0) sum += pf[i - 1];
                    if (i < len - 1) sum += sf[i + 1];
                    if (sum < mn) mn = sum;
                }
                ans += mn;
                free(pf);
                free(sf);
            } else {
                for (int i = 1; i < len; i += 2) ans += m[j][i] - m[j][i - 1];
            }
        }
    }
    
    printf("%lld\n", ans);
    assert(ans >= 0); // POST: the result is non-negative
    free(m[0]);
    free(m[1]);
}

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: TCS is in valid range
    for (int TC = 1; TC <= TCS; ++TC) {
        solve();
    }
    return 0;
}