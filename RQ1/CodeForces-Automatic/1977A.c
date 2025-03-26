#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases must be between 1 and 100

    for (int TC = 0; TC < TCS; ++TC)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 100); // PRE: n must be between 1 and 100
        assert(m >= 1 && m <= 100); // PRE: m must be between 1 and 100
        
        if ((n + m) % 2 != 0 || n < m)
            printf("No\n");
        else
            printf("Yes\n");

        assert((n + m) % 2 == 0 && n >= m || (n + m) % 2 != 0 || n < m); // POST: Condition for output
    }
    return 0;
}