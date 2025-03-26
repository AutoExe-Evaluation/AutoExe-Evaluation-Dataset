#include <stdio.h>
#include <assert.h>

int main()
{
    int n, a, b, min = 0, p = 0;
    scanf("%d", &n);
    assert(n >= 2 && n <= 1000); // PRE: n is within the given bounds
    while (n--)
    {
        scanf("%d %d", &a, &b);
        assert(a >= 0 && a <= 1000); // PRE: a is within the given bounds
        assert(b >= 0 && b <= 1000); // PRE: b is within the given bounds
        p = p - a + b;
        if (p > min) min = p;
    }
    printf("%d\n", min);
    assert(min >= 0); // POST: min capacity should be non-negative
    return 0;
}