#include <stdio.h>
#include <assert.h>

#define int long long

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int TC = 0;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4

    while (TC--) {
        int a = 0, b = 0;
        scanf("%lld %lld", &a, &b);
        assert(a >= 1 && a < b && b <= 1000000000); // PRE: 1 <= a < b <= 10^9

        int ans = lcm(a, b);
        if (ans != b) {
            printf("%lld\n", ans);
            assert(ans > b); // POST: ans > b
        } else {
            printf("%lld\n", b * (b / a));
            int x = b * (b / a);
            assert(x > b && x % a == 0 && x % b == 0); // POST: x > b and x is divisible by a and b
        }
    }
    return 0;
}