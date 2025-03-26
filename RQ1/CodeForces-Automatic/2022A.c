#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases should be in range [1, 1000]

    while (TCS--) {
        int n, r;
        scanf("%lld%lld", &n, &r);
        assert(n >= 1 && n <= 100); // PRE: Number of families should be in range [1, 100]
        assert(r >= 1 && r <= 500); // PRE: Number of rows should be in range [1, 500]

        int rem = 0;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 10); // PRE: Family members should be in range [1, 10]

            r -= x / 2;
            ans += (x / 2) * 2;
            rem += (x % 2);
        }

        // POST: The number of happy people calculated based on the arrangement
        printf("%lld\n", ans + (2 * r < rem ? 2 * r : rem));
    }
    
    return 0;
}