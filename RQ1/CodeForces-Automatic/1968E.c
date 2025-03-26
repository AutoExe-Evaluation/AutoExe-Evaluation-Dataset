#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 50); // PRE: 1 <= TCS <= 50

    while (TCS--)
    {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 1000); // PRE: 2 <= n <= 1000

        for (int i = 1; i <= n; ++i)
        {
            printf("%d %d\n", i, i - (i == 2));
        }
    }
    
    // POST: The output consists of n points that maximize the size of the set of distinct Manhattan distances.
    return 0;
}