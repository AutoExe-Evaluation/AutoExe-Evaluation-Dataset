#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5
        char s[n + 1], f[n + 1];
        scanf("%s %s", s, f);
        
        int x = 0, y = 0, m = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') x++;
            if (f[i] == '1') y++;
            if (s[i] != f[i]) m++;
        }
        
        int r = abs(x - y);
        int ans = r + (m - r) / 2;
        printf("%lld\n", ans);
        
        assert(ans >= 0); // POST: Minimum operations must be non-negative
    }
    return 0;
}