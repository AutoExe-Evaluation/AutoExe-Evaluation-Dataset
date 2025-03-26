#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) {
        long long a, b, c, ans;
        scanf("%lld %lld %lld", &a, &b, &c);
        assert(a >= 0 && b >= 0 && c >= 0); // PRE: 0 ≤ a, b, c ≤ 10^9
        
        ans = a;
        ans += b / 3;
        b %= 3;

        if (b && c < 3 - b) {
            printf("-1\n");
            continue;
        }

        if (b) {
            ans++;
            c -= 3 - b;
        }

        ans += c / 3;
        if (c % 3)
            ans++;
        
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: Minimum number of tents must be non-negative
    }

    return 0;
}