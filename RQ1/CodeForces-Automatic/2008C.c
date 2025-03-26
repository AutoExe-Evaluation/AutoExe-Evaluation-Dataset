#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ TCS ≤ 10^4

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int l, r;
        scanf("%lld %lld", &l, &r);
        assert(l >= 1 && l <= r && r <= 1000000000); // PRE: 1 ≤ l ≤ r ≤ 10^9
        
        int ct = 1;
        int d = 0;
        while (l <= r)
        {
            d++;
            l += d;
        }
        printf("%lld\n", d);
        assert(d >= 0); // POST: d is non-negative
    }
    return 0;
}