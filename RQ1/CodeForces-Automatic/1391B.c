#include <stdio.h>
#include <string.h>
#include <assert.h>

#define int long long

int main()
{
    int TC;
    scanf("%lld", &TC); // PRE: TC >= 1
    while (TC--)
    {
        int n, m;
        scanf("%lld %lld", &n, &m); // PRE: n >= 1, m >= 1
        int ct = 0;
        for (int i = 0; i < n; ++i)
        {
            char s[101];
            scanf("%s", s);
            if (i + 1 < n)
            {
                if (s[m - 1] == 'R')
                    ct++;
            }
            else
            {
                for (int j = 0; j < m - 1; ++j)
                {
                    if (s[j] == 'D')
                        ct++;
                }
            }
        }
        printf("%lld\n", ct); // POST: ct is the minimum number of changes needed
        assert(ct >= 0); // POST: ct is non-negative as it counts changes
    }
    return 0;
}