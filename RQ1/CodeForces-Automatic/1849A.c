#include <stdio.h>
#include <assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be in [1, 1000]
    
    while (TC--) {
        int b, c, h;
        scanf("%d %d %d", &b, &c, &h);
        assert(b >= 2 && b <= 100); // PRE: Number of pieces of bread should be in [2, 100]
        assert(c >= 1 && c <= 100); // PRE: Number of slices of cheese should be in [1, 100]
        assert(h >= 1 && h <= 100); // PRE: Number of slices of ham should be in [1, 100]

        int result;
        if (b == c + h)
            result = b + c + h - 1;
        else if (b > c + h)
            result = 2 * (c + h) + 1;
        else
            result = 2 * b - 1;

        printf("%d\n", result);
        assert(result == (b >= 2 && c >= 1 && h >= 1) ? result : -1); // POST: The result should be valid based on b, c, and h
    }
    return 0;
}