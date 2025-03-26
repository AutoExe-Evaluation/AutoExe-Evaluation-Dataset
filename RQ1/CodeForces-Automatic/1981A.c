#include <stdio.h>
#include <math.h>
#include <assert.h>

int main()
{
    int TCS = 1;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4
    for (int TC = 1; TC <= TCS; ++TC)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        assert(l >= 1 && r >= l && r <= 1000000000); // PRE: 1 ≤ l ≤ r ≤ 10^9
        assert(2 * l <= r); // PRE: 2l ≤ r
        if (r % 2 == 1) r--;
        long long ans = log2(r);
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: max score is non-negative
    }
    return 0;
}