#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases is within limits
    while (TC--) 
    {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        assert(n >= m && k >= 1 && k <= m); // PRE: constraints of n, m, k
        
        int a[MAXN], b[MAXN];
        int cta[1000001] = {0}, ctb[1000001] = {0};
        
        for (int i = 0; i < n; i++) 
        {
            scanf("%d", &a[i]);
            assert(a[i] >= 1 && a[i] <= 1000000); // PRE: elements of array a within range
        }
        
        for (int i = 0; i < m; i++) 
        {
            scanf("%d", &b[i]);
            assert(b[i] >= 1 && b[i] <= 1000000); // PRE: elements of array b within range
        }
        
        for (int i = 0; i < m; i++) 
            ctb[b[i]]++;

        for (int i = 0; i < m; i++) 
            cta[a[i]]++;

        int ans = 0, ct = 0;
        for (int i = 0; i <= 1000000; i++) 
            ct += (cta[i] < ctb[i]) ? cta[i] : ctb[i];

        if (ct >= k) 
            ans++;

        for (int i = m; i < n; i++) 
        {
            cta[a[i - m]]--;
            if (ctb[a[i - m]] > cta[a[i - m]]) 
                ct--;
            cta[a[i]]++;
            if (ctb[a[i]] >= cta[a[i]]) 
                ct++;
            if (ct >= k) 
                ans++;
        }

        printf("%d\n", ans);
        assert(ans >= 0); // POST: the answer is non-negative
    }
    return 0;
}