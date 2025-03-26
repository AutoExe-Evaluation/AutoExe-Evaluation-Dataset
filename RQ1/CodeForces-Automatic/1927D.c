#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main()
{
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--) 
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 200000); // PRE: 2 ≤ n ≤ 2 * 10^5

        int *v = (int *)malloc(n * sizeof(int));
        int *next = (int *)malloc(n * sizeof(int));
        
        for (int i = 0; i < n; ++i) 
        {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000); // PRE: 1 ≤ a[i] ≤ 10^6
        }
        
        next[0] = -1;
        for (int i = 1; i < n; ++i)
        {
            if (v[i] == v[i - 1]) 
                next[i] = next[i - 1];
            else 
                next[i] = i - 1;
        }
        
        int q;
        scanf("%lld", &q);
        assert(q >= 1 && q <= 200000); // PRE: 1 ≤ q ≤ 2 * 10^5
        
        while (q--)
        {
            int l, r;
            scanf("%lld %lld", &l, &r);
            l--, r--;
            assert(l >= 0 && r < n && l < r); // PRE: 1 ≤ l ≤ r ≤ n
            
            if (next[r] < l) 
                printf("-1 -1\n");
            else 
                printf("%lld %lld\n", next[r] + 1, r + 1);
        }
        printf("\n");
        
        free(v);
        free(next);
    }
    
    return 0;
} // POST: For every query, output correct indices i and j or -1 -1 if not found.