#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int main()
{
    long long q;
    scanf("%lld", &q);
    
    assert(q >= 1 && q <= 10000); // PRE: 1 ≤ n ≤ 10000
    
    long long mn = -2000000000;
    long long mx = 2000000000;
    
    while(q--)
    {
        char s[3];
        long long n;
        char c;
        scanf("%s %lld %c", s, &n, &c);
        
        assert(n >= -1000000000 && n <= 1000000000); // PRE: -10^9 ≤ x ≤ 10^9

        if(strcmp(s, ">=") == 0)
        {
            if(c == 'Y')
            {
                if(mn < n) mn = n;
            }
            else
            {
                if(mx > n - 1) mx = n - 1;
            }
        }
        else if(strcmp(s, "<=") == 0)
        {
            if(c == 'Y')
            {
                if(mx > n) mx = n;
            }
            else
            {
                if(mn < n + 1) mn = n + 1;
            }
        }
        else if(strcmp(s, ">") == 0)
        {
            if(c == 'Y')
            {
                if(mn < n + 1) mn = n + 1;
            }
            else
            {
                if(mx > n) mx = n;
            }
        }
        else if(strcmp(s, "<") == 0)
        {
            if(c == 'Y')
            {
                if(mx > n - 1) mx = n - 1;
            }
            else
            {
                if(mn < n) mn = n;
            }
        }
    }
    
    assert(mn <= mx); // POST: If mn > mx, then "Impossible"
    if(mn > mx)
    {
        printf("Impossible\n");
    }
    else
    {
        printf("%lld\n", mn);
    }
    
    return 0;
}