#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int solve(int n, int *v)
{
    int l = -1, r = -1;
    for (int i = 0; i < n; ++i)
    {
        if (v[i])
        {
            r = i;
            if (l == -1) l = i;
        }
    }
    
    assert(n > 0); // PRE: n is positive
    if (l == -1)
        return 0;
    else
    {
        for (int i = l; i <= r; ++i)
        {
            if (v[i] == 0)
            {
                return 2;
            }
        }
        return 1;
    }
}

int main()
{
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= TC <= 10^4
    while (TC--) 
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 100000); // PRE: 1 <= n <= 10^5
        int *v = (int *)malloc(n * sizeof(int));
        
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", &v[i]);
            assert(v[i] >= 0 && v[i] <= 1000000000); // PRE: 0 <= v[i] <= 10^9
        }
        int result = solve(n, v);
        printf("%lld\n", result);
        assert(result >= 0 && result <= 2); // POST: Result must be in {0, 1, 2}
        free(v);
    }
    return 0;
}