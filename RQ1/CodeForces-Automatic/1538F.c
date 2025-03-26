#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4
    for (int TC = 1; TC <= TCS; ++TC) {
        int l, r;
        scanf("%d %d", &l, &r);
        assert(l < r && l >= 1 && r <= 1000000000); // PRE: 1 ≤ l < r ≤ 10^9
        int ct = 0;
        while (l || r) {
            ct += r - l;
            l /= 10;
            r /= 10;
        }
        printf("%d\n", ct);
        assert(ct >= 0); // POST: Total changed digits should be non-negative
    }
    return 0;
}