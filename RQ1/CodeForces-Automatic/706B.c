#include <stdio.h>
#include <assert.h>

int main()
{
    long long n;
    long long N = 1e5 + 10;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 100000); // PRE: n is within bounds
    long long shop[N] = {0};

    for (long long i = 0; i < n; ++i)
    {
        long long x;
        scanf("%lld", &x);
        assert(x >= 1 && x <= 100000); // PRE: price x is within bounds
        shop[x]++;
    }

    long long presum[N] = {0};
    for (long long i = 1; i < N; ++i)
    {
        presum[i] = presum[i - 1] + shop[i]; 
    }
    
    int q;
    scanf("%d", &q);
    assert(q >= 1 && q <= 100000); // PRE: q is within bounds

    while (q--)
    {
        long long x;
        scanf("%lld", &x);
        assert(x >= 1 && x <= 1000000000); // PRE: spending limit m is within bounds

        if (x < N)
            printf("%lld\n", presum[x]);
        else 
            printf("%lld\n", presum[N - 1]);
    }
    
    // POST: For each day, the output is the number of shops 
    // where Vasiliy can buy the drink within his budget
    return 0;
}