#include <stdio.h>
#include <limits.h>
#include <assert.h>

#define ll long long

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Test cases should be between 1 and 100
    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 1000); // PRE: n should be between 1 and 1000
        assert(m >= 1 && m <= 1000); // PRE: m should be between 1 and 1000
        if(m > 2 * n - 1)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        for(int i = 0; i < 2 * n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                int color = ((i + j) % (2 * n)) / 2 + 1;
                printf("%d", color);
                if(j != m - 1) printf(" ");
            }
            printf("\n");
        }
        assert(m <= 2 * n - 1); // POST: Ensured condition after producing output
    }
    return 0;
}