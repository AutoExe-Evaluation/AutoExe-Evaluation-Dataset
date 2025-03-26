#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

int main()
{
    ll n, k;
    scanf("%lld %lld", &n, &k);
    
    assert(n >= 1 && n <= 1000000000000000); // PRE: n is within the bounds
    assert(k >= 1 && k <= 1000000000); // PRE: k is within the bounds
    
    ll *v = (ll *)malloc(2 * n * sizeof(ll));
    ll count = 0;

    for(ll i = 1; i * i <= n; ++i)
    {
        if(n % i == 0)
        {
            v[count++] = i;
            if(i != n / i)
                v[count++] = n / i;
        }
    }
    
    // Sort the divisors
    for (ll i = 0; i < count - 1; i++)
    {
        for (ll j = 0; j < count - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                ll temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    assert(count >= 0); // PRE: count is non-negative
    if(k > count)  
    {
        printf("-1\n");
        assert(0); // POST: if there are fewer than k divisors, output -1
    }
    else 
    {
        printf("%lld\n", v[k - 1]);
        assert(v[k - 1] > 0); // POST: k-th smallest divisor must be positive
    }

    free(v);
    return 0;
}