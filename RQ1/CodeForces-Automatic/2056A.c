#include <stdio.h>
#include <assert.h>

int main() {
    int TCS = 1;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Test cases are within the allowed range
    while (TCS--) {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 100); // PRE: n is within valid range
        assert(m >= 2 && m <= 100); // PRE: m is within valid range

        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            assert(x >= 1 && x <= m - 1); // PRE: x is within valid range
            assert(y >= 1 && y <= m - 1); // PRE: y is within valid range
            
            if (i == 0) {
                ans += 2 * m;
            } else {
                ans += 2 * x + 2 * y;
            }
        }
        ans += 2 * m;
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: The computed perimeter is non-negative
    }
    return 0;
}