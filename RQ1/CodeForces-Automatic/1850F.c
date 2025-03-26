#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: 1 ≤ t ≤ 100
    
    while (TCS--)
    {
        ll n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 ≤ n ≤ 2 * 10^5
        
        ll *freq = (ll *)calloc(n + 1, sizeof(ll));
        ll *mp = (ll *)calloc(n + 1, sizeof(ll));
        
        for(int i = 0; i < n; ++i)
        {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
            if(x <= n)  freq[x]++;
        }

        for(int i = 1; i <= n; ++i)
        {
            for(int j = i; j <= n; j += i)
                mp[j] += freq[i];
        }
        
        ll max_frogs = 0;
        for (int i = 1; i <= n; ++i) {
            if (mp[i] > max_frogs) {
                max_frogs = mp[i];
            }
        }
        printf("%lld\n", max_frogs);
        
        free(freq);
        free(mp);
        assert(max_frogs >= 0); // POST: max_frogs should be >= 0
    }
    return 0;
}