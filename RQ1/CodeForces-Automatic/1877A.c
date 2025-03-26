#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: 1 <= t <= 500
    
    while (TC--) 
    {
        int n, total = 0;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 100); // PRE: 2 <= n <= 100
        
        for(int i = 1; i < n; ++i)
        {
            int x;
            scanf("%lld", &x);
            assert(x >= -100 && x <= 100); // PRE: -100 <= a_i <= 100
            total += x;
        }
        int missing_team_efficiency = -total;
        printf("%lld\n", missing_team_efficiency);
        assert(missing_team_efficiency >= -100 && missing_team_efficiency <= 100); // POST: -100 <= efficiency <= 100
    }
    
    return 0;
}