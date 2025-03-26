#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= TCS <= 1000
    for (int TC = 1; TC <= TCS; ++TC)
    {
        long long n, s;
        scanf("%lld %lld", &n, &s);
        assert(n >= 1 && n <= 10); // PRE: 1 <= n <= 10
        assert(s >= 1 && s <= 100); // PRE: 1 <= s <= 100
        
        long long mn = LLONG_MAX, mx = 0;
        for(long long i = 0; i < n; ++i)
        {
            long long x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 100); // PRE: 1 <= x_i <= 100
            if(x < mn) mn = x;
            if(x > mx) mx = x;
        }
        
        long long result = mx - mn + (abs(mx - s) < abs(mn - s) ? abs(mx - s) : abs(mn - s));
        printf("%lld\n", result);
        assert(result >= 0); // POST: result >= 0 (number of steps cannot be negative)
    }
    return 0;
}