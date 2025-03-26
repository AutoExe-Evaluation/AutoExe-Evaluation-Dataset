#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_N 5000

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        int n;
        char s[MAX_N + 1];
        scanf("%d %s", &n, s);
        assert(n >= 1 && n <= 5000); // PRE: 1 <= n <= 5000
        assert(strlen(s) == n); // PRE: length of string matches n
        
        int ans = 1;
        int flip[MAX_N] = {0};

        for (int k = 2; k <= n; ++k) {
            memset(flip, 0, sizeof(flip));
            int f = 0;

            for (int i = 0; i <= n - k; ++i) {
                if ((f + s[i] - '0') % 2 == 0) {
                    f ^= 1;
                    flip[i + k - 1] = 1;
                }
                f ^= flip[i];
            }

            int ok = 1;
            for (int i = n - k + 1; i < n; ++i) {
                ok &= ((f + s[i] - '0') & 1);
                f ^= flip[i];
            }

            if (ok) ans = k;
        }
        printf("%d\n", ans);
        assert(ans >= 1 && ans <= n); // POST: maximum k is within bounds
    }
    return 0;
}