#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 200000); // PRE: n should be within the constraints
    int suf_even = 0, suf_odd = 0, pre_even = 0, pre_odd = 0;
    int v[n + 1];
    
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &v[i]);
        assert(v[i] >= 1 && v[i] <= 10000); // PRE: each weight should be within the constraints
        if (i & 1)
            suf_odd += v[i];
        else
            suf_even += v[i];
    }
    
    int ct = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i & 1)
            suf_odd -= v[i];
        else
            suf_even -= v[i];
        
        if (suf_even + pre_odd == suf_odd + pre_even)
        {
            ct++;
        }
        
        if (i & 1)
            pre_odd += v[i];
        else
            pre_even += v[i];
    }
    
    printf("%lld\n", ct);
    assert(ct >= 0 && ct <= n); // POST: The count of good candies should be within valid range
    return 0;
}