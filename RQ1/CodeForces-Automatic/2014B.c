#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be within the given range.

    while (TCS--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 1 && n <= 1000000000); // PRE: n should be within the given range.
        assert(k >= 1 && k <= n); // PRE: k should be within the given range.

        int odd = k / 2;
        if (n & 1 && k & 1) odd++;
        if (odd & 1) {
            printf("NO\n");
            assert(odd % 2 == 1); // POST: If the output is "NO", odd should be odd.
        } else {
            printf("YES\n");
            assert(odd % 2 == 0); // POST: If the output is "YES", odd should be even.
        }
    }
    return 0;
}