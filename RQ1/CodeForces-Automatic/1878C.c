#include <stdio.h>
#include <assert.h>

#define ll long long

int main() {
    int TC = 0;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases is within the valid range

    while (TC--) {
        ll n, k, x;
        scanf("%lld %lld %lld", &n, &k, &x);
        assert(n >= 1 && n <= 200000); // PRE: n is within the valid range
        assert(k >= 1 && k <= n); // PRE: k is within the valid range
        assert(x >= 1 && x <= 40000000000); // PRE: x is within the valid range
        
        ll max = (n * (n + 1) - (n - k) * (n - k + 1)) / 2;
        ll min = k * (k + 1) / 2;

        if (x <= max && x >= min) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    // POST: The output is correct if for all test cases the conditions are met.
    return 0;
}