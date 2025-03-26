#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases should be within the range [1, 100].

    while (TC--)
    {
        int n, k, x;
        scanf("%d %d %d", &n, &k, &x);
        assert(n >= 1 && n <= 100 && k >= x && x <= k); // PRE: Constraints for n, k, and x are met.

        if (k == 1)
            printf("NO\n");
        else if (x != 1)
        {
            printf("YES\n");
            printf("%d\n", n);
            for (int i = 0; i < n; i++)
                printf("1 ");
            printf("\n");
            assert(n >= 1 && n <= 100); // POST: Sum of output integers equals n.
        }
        else if (n % 2 == 0)
        {
            printf("YES\n");
            printf("%d\n", n / 2);
            for (int i = 0; i < n / 2; i++)
                printf("2 ");
            printf("\n");
            assert(n % 2 == 0 && (n / 2) * 2 == n); // POST: Sum of output integers equals n.
        }
        else if (k == 2)
            printf("NO\n");
        else
        {
            printf("YES\n");
            printf("%d\n", n / 2);
            for (int i = 0; i < n / 2 - 1; i++)
                printf("2 ");
            printf("3\n");
            assert((n / 2 - 1) * 2 + 3 == n); // POST: Sum of output integers equals n.
        }
    }
    return 0;
}