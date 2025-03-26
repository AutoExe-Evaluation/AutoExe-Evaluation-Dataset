#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 51

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 2000); // PRE: 1 <= T <= 2000
    while (TC--)
    {
        int n, m;
        char s[MAX_LEN], t[MAX_LEN];
        scanf("%d %d", &n, &m);
        assert(n >= 1 && n <= 50); // PRE: 1 <= n <= 50
        assert(m >= 1 && m <= 50); // PRE: 1 <= m <= 50
        scanf("%s %s", s, t);
        
        int valid = 1;
        for (int i = 1; i < m; ++i)
        {
            if (t[i] == t[i - 1])
            {
                valid = 0;
                break;
            }
        }
        
        for (int i = 1; i < n; ++i)
        {
            if (s[i] == s[i - 1])
            {
                if (s[i - 1] == t[0] || s[i] == t[m - 1] || !valid)
                {
                    printf("NO\n");
                    return 0;
                }
            }
        }
        
        printf("YES\n");
    }
    return 0;
    // POST: The output correctly indicates if it is possible to make s good for each test case.
}