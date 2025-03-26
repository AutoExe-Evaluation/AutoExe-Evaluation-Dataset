#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within range

    while (TCS--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 200000); // PRE: Length of string is within range
        char s[200001];
        scanf("%s", s);

        long long r = (long long)sqrt(n);
        assert(r * r <= n); // Check if square root is valid

        if (r * r != n) {
            printf("NO\n");
            continue; // POST: if r*r != n, it cannot form a square matrix
        }

        char v[200001][200001];
        long long c = 0;
        for (long long i = 0; i < n; i += r) {
            strncpy(v[c], s + i, r);
            v[c][r] = '\0';
            c++;
        }

        int isBeautiful = 1; // Assume it is beautiful
        for (long long i = 0; i < r; ++i) {
            for (long long j = 0; j < r; ++j) {
                if (j == 0 || j == r - 1 || i == 0 || i == r - 1) {
                    if (v[i][j] != '1') {
                        isBeautiful = 0; // Not a beautiful matrix
                    }
                } else {
                    if (v[i][j] != '0') {
                        isBeautiful = 0; // Not a beautiful matrix
                    }
                }
            }
        }

        // POST: If matrix is beautiful, print YES, otherwise NO
        if (isBeautiful) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}