#include <stdio.h>
#include <assert.h>

#define ll long long

int main()
{
    ll TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases is within valid range

    while (TCS--)
    {
        ll n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: number of elements is within valid range

        ll mx = 0, ct = 0, sum = 0;
        for (ll i = 0; i < n; ++i)
        {
            ll x;
            scanf("%lld", &x);
            assert(x >= 0 && x <= 1000000000); // PRE: elements are within valid range

            sum += x;
            if (x > mx) mx = x;
            if (sum - mx == mx) ct++;
        }
        printf("%lld\n", ct);
        assert(ct >= 0 && ct <= n); // POST: count of good prefixes must be valid
    }
    
    return 0;
}