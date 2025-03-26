#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases must be between 1 and 100
    
    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n, k;
        scanf("%d %d", &n, &k);
        
        assert(n >= 1 && n <= 1000); // PRE: n must be between 1 and 1000
        assert(k >= 1 && k <= n && n % k == 0); // PRE: k must be a divisor of n
        
        int v[n][n];
        int ans[n/k][n/k];
        
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)  
            {
                char c;
                scanf(" %c", &c);
                v[i][j] = c - '0';
            }
        }
        
        for(int i = 0; i < n; i += k)
        {
            for(int j = 0; j < n; j += k)
            {
                ans[i/k][j/k] = v[i][j];
            }
        }
        
        for(int i = 0; i < n/k; ++i)
        {
            for(int j = 0; j < n/k; ++j)
            {
                printf("%d", ans[i][j]);
            }
            printf("\n");
        }
        
        assert(n % k == 0); // POST: The output grid dimensions must match n/k x n/k
    }
    return 0;
}