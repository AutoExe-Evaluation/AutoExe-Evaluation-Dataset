#include <stdio.h>
#include <assert.h>

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 5000); // PRE: Number of test cases in valid range

    for (long long TC = 1; TC <= TCS; ++TC) {
        long long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        assert(a >= 1 && a <= 100000000 && b >= 1 && b <= 100000000 && c >= 1 && c <= 100000000); // PRE: a, b, c are within specified limits

        if ((a + c - 2 * b) % 3) {
            printf("1\n");
            assert((a + c - 2 * b) % 3 != 0); // POST: if printed 1, deviation is non-zero
        } else {
            printf("0\n");
            assert((a + c - 2 * b) % 3 == 0); // POST: if printed 0, deviation is zero
        }
    }
    return 0;
}