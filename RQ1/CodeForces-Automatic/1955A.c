#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TC--)
    {
        int n, a, b;
        scanf("%d %d %d", &n, &a, &b);
        assert(n >= 1 && n <= 100 && a >= 1 && a <= 30 && b >= 1 && b <= 30); // PRE: 1 ≤ n ≤ 100, 1 ≤ a, b ≤ 30

        int cost;
        if (2 * a <= b)
            cost = n * a;
        else
        {
            if (n % 2)
                cost = (n / 2) * b + a;
            else
                cost = (n / 2) * b;
        }
        
        printf("%d\n", cost);
        assert(cost >= 0); // POST: cost should be non-negative
    }
    
    return 0;
}