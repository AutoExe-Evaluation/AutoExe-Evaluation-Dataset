#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS); // PRE: TCS should be between 1 and 1000
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is valid

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n, m;
        scanf("%d %d", &n, &m); // PRE: n * m <= 200000
        assert(n * m <= 200000); // PRE: Grid size is within limits
        
        char **v = (char **)malloc(n * sizeof(char *));
        for (int i = 0; i < n; ++i)
        {
            v[i] = (char *)malloc((m + 1) * sizeof(char));
            scanf("%s", v[i]);
        }

        int x = 0, y = 0, mx = 0, my = 0;
        for (int i = 0; i < n; ++i)
        {
            int ct = 0;
            for (int j = 0; j < m; ++j)
            {
                if (v[i][j] == '#')
                    ct++;
            }
            if (ct > mx)
            {
                mx = ct;
                x = i + 1;
            }
        }
        for (int j = 0; j < m; ++j)
        {
            int ct = 0;
            for (int i = 0; i < n; ++i)
            {
                if (v[i][j] == '#')
                    ct++;
            }
            if (ct > my)
            {
                my = ct;
                y = j + 1;
            }
        }
        printf("%d %d\n", x, y); // POST: Output coordinates of the circle center
        assert(x >= 1 && x <= n); // POST: x is a valid row index
        assert(y >= 1 && y <= m); // POST: y is a valid column index

        for (int i = 0; i < n; ++i)
        {
            free(v[i]);
        }
        free(v);
    }
    return 0;
}