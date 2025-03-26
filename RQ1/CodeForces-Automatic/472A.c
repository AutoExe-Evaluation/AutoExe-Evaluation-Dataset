#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MAXN 1000010

bool is_prime[MAXN];

void sieve() 
{
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAXN; ++i) 
    {
        if (is_prime[i]) 
        {
            for (int j = i * i; j <= MAXN; j += i) 
                is_prime[j] = false;
        }
    }
}

int main()
{
    long long n;
    scanf("%lld", &n);
    assert(n >= 12); // PRE: n should be no less than 12
    sieve();
    for(int i = 4; 2 * i <= n; i += 2)
    {
        if(!is_prime[i] && !is_prime[n - i])
        {
            printf("%d %lld\n", i, n - i);
            assert(i > 1 && (n - i) > 1); // POST: both x and y should be composite numbers greater than 1
            break;
        }
    }
    return 0;
}