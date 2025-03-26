#include <stdio.h>
#include <assert.h>

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is valid
    for (int TC = 1; TC <= TCS; ++TC) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 99 && n % 2 == 1); // PRE: n is valid and odd
        long long mx = 0;
        for (int i = 1; i <= n; ++i) {
            long long x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 100); // PRE: Each element is valid
            if (i & 1) mx = max(mx, x);
        }
        printf("%lld\n", mx);
        assert(mx >= 1 && mx <= 100); // POST: Maximum element from odd indices is in range
    }
    return 0;
}