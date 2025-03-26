#include <stdio.h>
#include <limits.h>
#include <assert.h>

int main() {
    long long TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be within valid range.
    
    while (TC--) {
        long long n, x;
        scanf("%lld %lld", &n, &x);
        assert(n >= 1 && n <= 50); // PRE: Number of gas stations should be within valid range.
        assert(x >= 2 && x <= 100); // PRE: Distance x should be within valid range.
        
        long long v[50];
        for (long long i = 0; i < n; ++i) {
            scanf("%lld", &v[i]);
            assert(v[i] > 0 && v[i] < x); // PRE: Gas station positions should be valid.
            if (i > 0) {
                assert(v[i] > v[i - 1]); // PRE: Gas station positions must be strictly increasing.
            }
        }
        
        long long mx = 0;
        for (long long i = 1; i < n; ++i) {
            long long dis = v[i] - v[i - 1];
            if (dis > mx) mx = dis;
        }
        
        long long ans = mx > 2 * (x - v[n - 1]) ? mx : 2 * (x - v[n - 1]);
        ans = ans > v[0] ? ans : v[0];
        
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: The gas tank volume must be non-negative.
    }
    return 0;
}