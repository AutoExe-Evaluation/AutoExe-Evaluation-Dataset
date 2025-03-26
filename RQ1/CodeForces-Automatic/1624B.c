#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4
    while (TC--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        assert(a > 0 && b > 0 && c > 0); // PRE: a, b, c are positive integers

        if ((2 * b - c) > 0 && (2 * b - c) % a == 0)
            printf("YES\n");
        else if ((a + c) % (2 * b) == 0)
            printf("YES\n");
        else if ((2 * b - a) > 0 && (2 * b - a) % c == 0)
            printf("YES\n");
        else
            printf("NO\n");

        // POST: The output will be "YES" or "NO" based on the conditions satisfied
    }
    return 0;
}