#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 200); // PRE: 1 <= TC <= 200
    
    while (TC--)
    {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200); // PRE: 1 <= n <= 200
        
        int a[n + 1];
        int sum = 0;
        
        for (int i = 1; i <= n; ++i)
        {
            a[i] = i;
            sum += i;
        }
        
        if (sum % n != 0)
        {
            int r = sum % n;
            a[r] = a[r] + r;
        }
        
        for (int i = 1; i <= n; ++i)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
        
        // POST: Every element a_i satisfies 1 <= a_i <= 1000, a_i is divisible by i, and sum(a) % n == 0
        assert(a[1] >= 1 && a[1] <= 1000); // Check first element
        for (int i = 2; i <= n; ++i)
        {
            assert(a[i] >= 1 && a[i] <= 1000); // Check each element
            assert(a[i] % i == 0); // Check divisibility
        }
        assert(sum % n == 0); // Check sum condition
    }
    
    return 0;
}