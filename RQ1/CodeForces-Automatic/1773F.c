#include <stdio.h>
#include <assert.h>

int main()
{
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);

    assert(n >= 1 && n <= 100); // PRE: n is in the range [1, 100]
    assert(a >= 0 && a <= 1000); // PRE: a is in the range [0, 1000]
    assert(b >= 0 && b <= 1000); // PRE: b is in the range [0, 1000]

    if (n == 1)
    {
        if (a == b)
        {
            printf("1\n");
            printf("%d:%d\n", a, b);
            return 0;
        }
        else
        {
            printf("0\n");
            printf("%d:%d\n", a, b);
            return 0;
        }
    }
    else if (n == a + b)
    {
        printf("0\n");
        for (int i = 1; i <= a; ++i)
            printf("1:0\n");
        for (int i = 1; i <= b; ++i)
            printf("0:1\n");
    }
    else if (n < a + b)
    {
        printf("0\n");
        
        if (n <= b)
        {
            int ct = 0;
            int zero = 1;
            if (a != 0)
            {
                printf("%d:0\n", a);
                zero = 0;
                ct++;
            }
            for (int i = ct + 1; i < n; ++i)
            {
                printf("0:1\n");
                ct++;
            }
            if (zero) printf("0:%d\n", b - ct);
            else printf("0:%d\n", b - ct + 1);
        }
        else if (n <= a)
        {
            int ct = 0;
            int zero = 1;
            if (b != 0)
            {
                printf("0:%d\n", b);
                ct++;
                zero = 0;
            }
            for (int i = ct + 1; i < n; ++i)
            {
                printf("1:0\n");
                ct++;
            }
            if (zero)
                printf("%d:0\n", a - ct);
            else 
                printf("%d:0\n", a - ct + 1);
        }
        else
        {
            int ct = 0;
            for (int i = 1; i <= a; ++i)
            {
                printf("1:0\n");
            }
            for (int i = 1; i < n - a; ++i)
            {
                printf("0:1\n");
                ct++;
            }
            printf("0:%d\n", b - ct);
        }
    }
    else
    {
        int draws = n - a - b;
        printf("%d\n", draws); // POST: draws is the minimum number of draws
        for (int i = 1; i <= draws; ++i)
        {
            printf("0:0\n");
        }
        for (int i = 1; i <= a; ++i)
        {
            printf("1:0\n");
        }
        for (int i = 1; i <= b; ++i)
        {
            printf("0:1\n");
        }
    }
    
    return 0;
}