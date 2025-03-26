#include <stdio.h>
#include <assert.h>

#define ll long long

int main()
{
    ll TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4

    for (ll TC = 1; TC <= TCS; ++TC)
    {
        ll n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 100000000000000); // PRE: 2 <= n <= 10^14

        if (n & (n - 1))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
    assert(TCS > 0); // POST: Function executed for all test cases
}