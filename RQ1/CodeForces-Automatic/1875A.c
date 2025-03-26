#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 2000); // PRE: 1 <= TC <= 2000

    while (TC--) {
        int a, b, n;
        scanf("%lld%lld%lld", &a, &b, &n);
        assert(b >= 1 && b <= a && a <= 1000000000); // PRE: 1 <= b <= a <= 10^9
        assert(n >= 1 && n <= 100); // PRE: 1 <= n <= 100

        int ans = b;
        for(int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: 1 <= x_i <= 10^9
            ans += (x < a - 1) ? x : (a - 1);
        }
        printf("%lld\n", ans);
        assert(ans >= b && ans <= a + n * (a - 1)); // POST: ans >= b and <= a + n * (a - 1)
    }

    return 0;
}