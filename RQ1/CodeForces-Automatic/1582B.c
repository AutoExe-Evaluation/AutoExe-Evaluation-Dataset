#include <stdio.h>
#include <math.h>
#include <assert.h>

#define ll long long

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 ≤ t ≤ 1000

    while (TC--) 
    {
        ll n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 60); // PRE: 1 ≤ n ≤ 60

        ll ct1 = 0, ct0 = 0;
        for(ll i = 0; i < n; i++)
        {
            int x;
            scanf("%d", &x);
            assert(x >= 0 && x <= 1000000000); // PRE: 0 ≤ a_i ≤ 10^9
            
            if(x == 1)
                ct1++;
            else if(x == 0)
                ct0++;
        }

        ll ans = 0;

        if(ct1 != 0)
        {
            if(ct0 == 0)
                ans = ct1;
            else
                ans = ct1 * pow(2, ct0);
        }

        printf("%lld\n", ans);
        assert(ans >= 0); // POST: Number of nearly full subsequences should be non-negative
    }
    
    return 0;
}