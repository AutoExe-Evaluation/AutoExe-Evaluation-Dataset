#include<stdio.h>
#include<limits.h>
#include<assert.h>

#define int long long

int main()
{
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 50); // PRE: Number of test cases should be within limits
    while (TC--) 
    {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 2000); // PRE: n should be within limits
        int v[n];
        for(int i = 0; i < n; i++)  
        {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 999); // PRE: each element should be positive and within limits
        }
        if(n == 1)
        {
            printf("0\n");
            continue; // POST: If there is only one element, maximum difference is 0
        }
        int mx = LLONG_MIN;
        for(int i = 1; i < n; ++i)
            if(v[i-1] - v[i] > mx)
                mx = v[i-1] - v[i];
        for(int i = 1; i < n; ++i)
            if(v[i] - v[0] > mx)
                mx = v[i] - v[0];
        for(int i = 0; i < n-1; ++i)
            if(v[n-1] - v[i] > mx)
                mx = v[n-1] - v[i];
        assert(mx >= 0); // POST: Maximum difference should be non-negative
        printf("%lld\n", mx);   
    }
    return 0;
}