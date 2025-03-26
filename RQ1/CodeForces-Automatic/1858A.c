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
        assert(a >= 1 && a <= 1000000000); // PRE: 1 ≤ a ≤ 10^9
        assert(b >= 1 && b <= 1000000000); // PRE: 1 ≤ b ≤ 10^9
        assert(c >= 1 && c <= 1000000000); // PRE: 1 ≤ c ≤ 10^9
        
        if (c % 2)
        {
            if (b > a)
                printf("Second\n");
            else
                printf("First\n");
        }
        else
        {
            if (a > b)
                printf("First\n");
            else
                printf("Second\n");
        }
    }
    assert(0 <= TC && TC <= 10000); // POST: Ensures TC is within limits after all test cases
    return 0;
}