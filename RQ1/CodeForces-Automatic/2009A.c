#include <stdio.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 55); // PRE: 1 <= TCS <= 55

    for (long long TC = 1; TC <= TCS; ++TC) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        assert(a >= 1 && a <= b && b <= 10); // PRE: 1 <= a <= b <= 10
        printf("%lld\n", b - a);
        assert(b - a == (b - a)); // POST: Minimum value of (c - a) + (b - c) is b - a
    }
    return 0;
}