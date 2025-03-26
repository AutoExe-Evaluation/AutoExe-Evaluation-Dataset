#include <stdio.h>
#include <assert.h>

int main()
{
    long long TCS;
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases t is in the range [1, 100]
    scanf("%lld", &TCS);
    
    for (long long TC = 1; TC <= TCS; ++TC)
    {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        assert(a >= 0 && a < 10); // PRE: a is in the range [0, 9]
        assert(b >= 0 && b < 10); // PRE: b is in the range [0, 9]
        
        int f = 1;
        if (a % 2 != 0) f = 0;
        else if (b % 2 != 0 && a < 2) f = 0;
        
        if (f) 
            printf("YES\n");
        else 
            printf("NO\n");

        assert(f || (!f && (a % 2 != 0 || (b % 2 != 0 && a < 2)))); // POST: The condition for the result to be "YES" or "NO" is correctly applied
    }
    return 0;
}