#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within the defined limits

    while (TCS--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 3 && n <= 200000); // PRE: Number of points should be within the defined limits
        
        bool one[n + 10], zero[n + 10];
        for (int i = 0; i < n + 10; i++) {
            one[i] = false;
            zero[i] = false;
        }
        int ct_one = 0, ct_zero = 0;

        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%lld %lld", &x, &y);
            assert(x >= 0 && x <= n); // PRE: x should be within valid range
            assert(y == 0 || y == 1);  // PRE: y should be either 0 or 1
            if (y) {
                one[x] = 1;
                ct_one++;
            } else {
                zero[x] = 1;
                ct_zero++;
            }
        }
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (one[i] && zero[i]) {
                ans += ct_one + ct_zero - 2;
            }
            if (one[i] && zero[i + 1] && one[i + 2]) {
                ans++;
            }
            if (zero[i] && one[i + 1] && zero[i + 2]) {
                ans++;
            }
        }
        
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: Number of distinct nondegenerate right triangles should be non-negative
    }
    
    return 0;
}