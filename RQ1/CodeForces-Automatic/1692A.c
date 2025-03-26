#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be within the range [1, 10000]

    while (TC--)
    {
        int a, b, c, d, count = 0;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        assert(a >= 0 && a <= 10000 && b >= 0 && b <= 10000 && c >= 0 && c <= 10000 && d >= 0 && d <= 10000); // PRE: Distances should be within the range [0, 10000]
        assert(a != b && a != c && a != d && b != c && b != d && c != d); // PRE: All distances must be distinct

        if (b > a) count++;
        if (c > a) count++;
        if (d > a) count++;

        printf("%d\n", count);
        assert(count >= 0 && count <= 3); // POST: Number of participants in front of Timur should be within the range [0, 3]
    }
    
    return 0;
}