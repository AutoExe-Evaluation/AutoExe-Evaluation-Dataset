#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: 1 <= TCS <= 100

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        assert(x >= 0 && x <= 9); // PRE: 0 <= x <= 9
        assert(y >= 0 && y <= 9); // PRE: 0 <= y <= 9
        
        if (x < y)
            printf("%d %d\n", x, y);
        else
            printf("%d %d\n", y, x);
        
        // POST: The output is always in the format "min max"
    }

    return 0;
}