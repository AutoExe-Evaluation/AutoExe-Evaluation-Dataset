#include <stdio.h>
#include <assert.h>

long long pow(long long x, long long y, long long m) {
    long long ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be between 1 and 10000

    for (int TC = 0; TC < TCS; ++TC) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        assert(a >= 1 && a <= 10 && b >= 1 && b <= 10 && c >= 1 && c <= 10 && d >= 1 && d <= 10); // PRE: Card values should be between 1 and 10

        int ans = 0;

        if (a > c) {
            if (b >= d) ans++;
        }
        if (a == c) {
            if (b > d) ans++;
        }
        if (a > d) {
            if (b >= c) ans++;
        }
        if (a == d) {
            if (b > c) ans++;
        }
        if (b > c) {
            if (a >= d) ans++;
        }
        if (b == c) {
            if (a > d) ans++;
        }
        if (b > d) {
            if (a >= c) ans++;
        }
        if (b == d) {
            if (a > c) ans++;
        }

        printf("%d\n", ans);
        assert(ans >= 0); // POST: The number of ways Suneet could win is non-negative
    }
    
    return 0;
}