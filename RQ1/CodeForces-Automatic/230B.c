#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define MAXN 1000000

bool is_prime[MAXN];

void sieve() 
{
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i < MAXN; ++i) 
        is_prime[i] = true;
    for (int i = 2; i * i < MAXN; ++i) 
    {
        if (is_prime[i]) 
        {
            for (int j = i * i; j < MAXN; j += i) 
                is_prime[j] = false;
        }
    }
}

int main()
{
    sieve();
    long long n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 100000); // PRE: n is between 1 and 100,000
    for (long long i = 0; i < n; ++i)
    {
        long long x;
        scanf("%lld", &x);
        assert(x >= 1 && x <= 1000000000000LL); // PRE: each x is between 1 and 10^12
        long long r = sqrt(x);
        if (r * r == x && is_prime[r]) 
            printf("YES\n");
        else 
            printf("NO\n");
    }
    return 0;
}