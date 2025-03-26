#include <stdio.h>
#include <assert.h>

#define ll long long

int main()
{
    int TC = 0;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: Number of test cases must be between 1 and 500.
    
    while (TC--) 
    {
        ll n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 500); // PRE: Size of the matrix must be between 1 and 500.
        
        int sum = 0;
        for(int i = 1; i <= n; ++i)
            sum += i * (2 * i - 1);
        
        printf("%d %d\n", sum, 2 * n);
        for(int i = n; i >= 1; --i)
        {
            printf("1 %d ", i);
            for(int j = 1; j <= n; ++j)
                printf("%d ", j);
            printf("\n");
            printf("2 %d ", i);
            for(int j = 1; j <= n; ++j)
                printf("%d ", j);
            printf("\n");
        }
        
        assert(sum == n * n * (n + 1) / 2); // POST: The calculated sum should be the maximum sum for the n x n matrix.
    }
    
    return 0;
}