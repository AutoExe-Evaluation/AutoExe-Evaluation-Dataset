#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases is within bounds
    while (TC--)
    {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(n >= 2 && n <= 200000 && n % 2 == 0); // PRE: n is even and within bounds
        assert(k >= 0 && k <= 1000000000); // PRE: k is within bounds

        if (k % 4 == 0)
        {
            printf("NO\n");
        }
        else if (k % 4 == 2)
        {
            printf("YES\n");
            for (int i = 1; i <= n; i += 2)
            {
                if ((i + 1) % 4)
                    printf("%d %d\n", i + 1, i);
                else
                    printf("%d %d\n", i, i + 1);
            }
        }
        else
        {
            printf("YES\n");
            for (int i = 1; i <= n; i += 2)
                printf("%d %d\n", i, i + 1);
        }
    }
    return 0;
} // POST: Program correctly outputs pairs or "NO" based on the divisibility condition.