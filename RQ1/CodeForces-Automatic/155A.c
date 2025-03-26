#include <stdio.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 1000); // PRE: n is within the valid range
    int best, worst, ct = 0;

    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        assert(x >= 0 && x <= 10000); // PRE: x is within the valid range
        if (i == 0)
            best = worst = x;
        if (x < worst)
        {
            ct++;
            worst = x;
        }
        else if (x > best)
        {
            ct++;
            best = x;
        }
    }
    printf("%d\n", ct);
    assert(ct >= 0); // POST: ct is non-negative as it counts amazing performances
    return 0;
}