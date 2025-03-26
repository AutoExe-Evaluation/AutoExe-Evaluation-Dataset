#include <stdio.h>
#include <assert.h>

int main()
{
    int a, b, i;
    scanf("%d %d", &a, &b);
    
    assert(a >= 1 && a <= b && b <= 10); // PRE: a and b are within bounds and a is less than or equal to b

    for (i = 1; a <= b; i++)
    {
        a = a * 3;
        b = b * 2;
    }

    printf("%d\n", i);

    assert(a > b); // POST: Limak's weight (a) is greater than Bob's weight (b)
}