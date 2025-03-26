#include <stdio.h>
#include <assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000
    while (TC--)
    {
        int n, x;
        scanf("%d %d", &n, &x);
        assert(n >= 1 && n <= 1000); // PRE: 1 <= n <= 1000
        assert(x >= 1 && x <= 1000); // PRE: 1 <= x <= 1000
        
        if (n < 3)
            printf("1\n");
        else
        {
            n = n - 2;
            int f;
            if (n % x == 0)
                f = n / x + 1;
            else
                f = n / x + 2;
            printf("%d\n", f);
            assert(f >= 1); // POST: floor number must be at least 1
        }
    }
    return 0;
}