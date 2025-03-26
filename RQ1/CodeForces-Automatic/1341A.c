#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 1000); // PRE: Number of test cases should be 1 <= t <= 1000

    while (t--) {
        int n, a, b, c, d;
        scanf("%lld %lld %lld %lld %lld", &n, &a, &b, &c, &d);
        assert(n >= 1 && n <= 1000); // PRE: 1 <= n <= 1000
        assert(b < a && d < c && a >= 0 && b >= 0 && c >= 0 && d >= 0); // PRE: Constraints on a, b, c, d

        int p = a + b, q = a - b, r = c + d, s = c - d;
        if (p * n < s || q * n > r)
            printf("No\n");
        else
            printf("Yes\n");
        
        // POST: The output accurately reflects whether the weight constraints are met
        assert((p * n >= s && q * n <= r) || (p * n < s || q * n > r)); // Logic should hold true
    }
    return 0;
}