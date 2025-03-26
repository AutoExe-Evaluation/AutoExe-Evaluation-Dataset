#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

int main()
{
    char s[1000001];
    scanf("%s", s);
    ll n = strlen(s);
    assert(n > 0); // PRE: The input string must be non-empty.

    int *opens = (int *)malloc(n * sizeof(int));
    int *start = (int *)malloc(n * sizeof(int));
    int *st = (int *)malloc(n * sizeof(int));
    int top = -1;

    for(int i = 0; i < n; ++i)
    {
        opens[i] = -1;
        start[i] = -1;
    }

    for(int i = 0; i < n; ++i)
    {
        if(s[i] == '(') 
        {
            st[++top] = i;
        }
        else
        {
            if(top >= 0)
            {
                ll open = st[top--];
                opens[i] = open;
                if(open > 0 && s[open - 1] == ')' && start[open - 1] != -1)
                    start[i] = start[open - 1];
                else
                    start[i] = open;
            }
        }
    }

    ll mx = 0, len = 0;
    ll *mp = (ll *)calloc(n + 1, sizeof(ll));
    for(int i = 0; i < n; ++i)
    {
        if(start[i] != -1)
        {
            len = i - start[i] + 1;
            mx = (mx > len) ? mx : len;
            mp[len]++;
        }
    }

    if(mx == 0)
        printf("0 1\n");
    else
        printf("%lld %lld\n", mx, mp[mx]);

    assert(mx >= 0); // POST: The maximum length must be non-negative.
    assert(mx == 0 || mp[mx] > 0); // POST: If the max length is greater than 0, there must be at least one such substring.

    free(opens);
    free(start);
    free(st);
    free(mp);
    
    return 0;
}