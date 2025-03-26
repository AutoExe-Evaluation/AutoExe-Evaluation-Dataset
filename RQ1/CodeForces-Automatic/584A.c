#include <stdio.h>
#include <assert.h>

int main()
{
    int n, t;
    scanf("%d %d", &n, &t);
    
    assert(n >= 1 && n <= 100); // PRE: n must be between 1 and 100
    assert(t >= 2 && t <= 10); // PRE: t must be between 2 and 10
    
    char s[101] = {0};

    if (t == 10)
    {
        if (n == 1)
        {
            printf("-1\n");
            return 0;
        }
        s[0] = '1';
        for (int i = 1; i < n; i++)
        {
            s[i] = '0';
        }
    }
    else
    {
        char c = t + '0';
        for (int i = 0; i < n; i++)
        {
            s[i] = c;
        }
    }
    s[n] = '\0';
    
    printf("%s\n", s);
    
    assert(s[0] != '0' && strlen(s) == n && (atoi(s) % t == 0)); // POST: number is n digits, > 0 and divisible by t
    return 0;
}