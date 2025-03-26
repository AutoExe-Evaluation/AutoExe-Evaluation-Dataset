#include <stdio.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    assert(n >= 1 && n <= 15); // PRE: n is within the range [1, 15]
    
    int v[15];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        assert(v[i] >= 1 && v[i] <= 180); // PRE: a_i is within the range [1, 180]
    }
    
    for (int mask = 0; mask < (1 << n); mask++) 
    {
        int sum = 0;
        for (int i = 0; i < n; i++) 
        {
            if (mask & (1 << i)) sum -= v[i];
            else sum += v[i];
        }
        
        if (sum % 360 == 0) 
        {
            printf("YES\n");
            assert(sum % 360 == 0); // POST: At least one combination leads to sum being a multiple of 360
            return 0;
        }
    }
    
    printf("NO\n");
    assert(1); // POST: No combination found, we print "NO"
    return 0;
}