#include <stdio.h>
#include <assert.h>

int main()
{
    int n, x = 0;

    // PRE: n should be in the range [1, 150]
    scanf("%d", &n);
    assert(n >= 1 && n <= 150); // PRE: n is between 1 and 150

    while (n--)
    {
        char op[4];
        scanf("%s", op);
        if (op[1] == '+')
            x++;
        else if (op[1] == '-')
            x--;
    }

    // POST: The final value of x is the result after processing n statements
    printf("%d\n", x);
    assert(x >= -n && x <= n); // POST: x is bounded by the number of operations

    return 0;
}