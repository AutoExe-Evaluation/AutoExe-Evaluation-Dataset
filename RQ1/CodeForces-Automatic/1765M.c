#include <stdio.h>
#include <assert.h>

void solve(long long n) {
    assert(n >= 2); // PRE: n should be at least 2
    long long ans = 1;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ans = n / i;
            break;
        }
    }
    printf("%lld %lld\n", ans, n - ans);
    assert(ans > 0 && (n - ans) > 0); // POST: both a and b must be positive
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: number of test cases should be within the given range
    for (int TC = 1; TC <= TCS; ++TC) {
        long long n;
        scanf("%lld", &n);
        solve(n);
    }
    return 0;
}