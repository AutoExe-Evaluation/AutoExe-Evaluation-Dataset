#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: number of test cases must be between 1 and 500

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100); // PRE: size of array must be between 1 and 100
        int last, ans = 0;

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: array elements must be between 1 and 10^9

            if (i == 0) {
                last = x & 1;
                continue;
            }
            if ((last + x) % 2 == 0)
                ans++;
            last = x & 1;
        }
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: number of operations must be non-negative
    }
    return 0;
}