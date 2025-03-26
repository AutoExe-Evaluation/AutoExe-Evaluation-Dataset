#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within bounds

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 1000); // PRE: Length of array is within bounds
        int ans = 0;

        for(int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 0 && x < (1 << 8)); // PRE: Each element is within bounds
            ans ^= x;
        }

        if(ans == 0 || n & 1) {
            printf("%lld\n", ans);
            assert(ans >= 0 && ans < (1 << 8)); // POST: Output x is valid if it exists
        } else {
            printf("-1\n");
            assert(ans == -1); // POST: Output -1 when there is no valid x
        }
    }
    return 0;
}