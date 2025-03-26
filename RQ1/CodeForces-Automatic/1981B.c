#include <stdio.h>
#include <assert.h>

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases should be within the bounds
    for (int TC = 1; TC <= TCS; ++TC) {
        long long n, m;
        scanf("%lld %lld", &n, &m);
        assert(n >= 0 && m >= 0 && n <= 1000000000 && m <= 1000000000); // PRE: n and m should be within the bounds
        long long l = max(0LL, n - m), r = n + m, ans = 0;
        for (int i = 0; i < 32; ++i) {
            long long p = l / (1 << i);
            long long q = r / (1 << i);
            if (p & 1 || q & 1 || p != q)
                ans |= (1 << i);
        }
        printf("%lld\n", ans);
        assert(ans >= 0 && ans <= (1LL << 32) - 1); // POST: final answer should be a valid 32-bit unsigned integer
    }
    return 0;
}