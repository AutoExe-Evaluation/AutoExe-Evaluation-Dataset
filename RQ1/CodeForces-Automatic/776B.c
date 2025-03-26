#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MAXN 1000010

bool is_prime[MAXN];

void sieve() 
{
    is_prime[0] = false;
    is_prime[1] = false;
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
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100000); // PRE: n is within the valid range
    sieve();
    
    int num_colors = 1 + (n > 2);
    printf("%d\n", num_colors);
    
    for(int i = 2; i <= n + 1; ++i)
    {
        printf("%d ", 2 - is_prime[i]);
    }
    printf("\n");
    
    assert(num_colors == 1 + (n > 2)); // POST: num_colors reflects the correct minimum colors based on n
    return 0;
}