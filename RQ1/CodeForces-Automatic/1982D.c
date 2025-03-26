#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define int long long

int gcd(int a, int b) {
    while (b) {
        a = a % b;
        a ^= b;
        b ^= a;
        a ^= b;
    }
    return a;
}

int main() {
    int TCS;
    scanf("%lld", &TCS); // PRE: TCS >= 1
    assert(TCS >= 1); // POST: Number of test cases is valid

    for (int TC = 1; TC <= TCS; TC++) {
        int n, m, k;
        scanf("%lld %lld %lld", &n, &m, &k);
        assert(n >= 1 && m >= 1 && k >= 1 && k <= (n < m ? n : m)); // PRE: Dimensions and k are valid

        int a[n][m], pf[n + 1][m + 1];
        memset(pf, 0, sizeof(pf));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%lld", &a[i][j]);
                assert(a[i][j] >= 0); // PRE: Heights are non-negative
            }
        }
        
        char b[n][m + 1];
        for (int i = 0; i < n; i++) {
            scanf("%s", b[i]);
            assert(strlen(b[i]) == m); // PRE: Each binary string has length m
        }
        
        int diff = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (b[i][j] == '1') {
                    diff += a[i][j];
                } else {
                    diff -= a[i][j];
                }
            }
        }
        
        diff = labs(diff);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int val = -1;
                if (b[i - 1][j - 1] == '1') {
                    val = 1;
                }
                pf[i][j] = val + pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1];
            }
        }
        
        int g = 0;
        for (int i = 1; i <= n - k + 1; i++) {
            for (int j = 1; j <= m - k + 1; j++) {
                int val = pf[i + k - 1][j + k - 1] - pf[i - 1][j + k - 1] - pf[i + k - 1][j - 1] + pf[i - 1][j - 1];
                g = gcd(g, labs(val));
            }
        }
        
        if (diff == 0) {
            printf("YES\n");
        } else if (g == 0) {
            printf("NO\n");
        } else {
            printf(diff % g == 0 ? "YES\n" : "NO\n");
        }
        assert((diff == 0 || g != 0) && (diff % g == 0 || g == 0)); // POST: Correct conditions for output based on diff and g
    }
    return 0;
}