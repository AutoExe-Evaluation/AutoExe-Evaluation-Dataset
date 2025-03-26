#include <stdio.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= t <= 1000
    for (long long TC = 1; TC <= TCS; ++TC) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 2000 && n % 2 == 0); // PRE: 2 <= n <= 2000 and n is even
        long long ans = n / 4;
        n %= 4;
        ans += n / 2;
        printf("%lld\n", ans);
        assert(ans >= 1); // POST: minimum number of animals is at least 1
    }
    return 0;
}