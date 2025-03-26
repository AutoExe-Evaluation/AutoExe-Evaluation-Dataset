#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4
    while (TC--)
    {
        int n;
        char c;
        scanf("%d %c", &n, &c);
        assert(n >= 1 && n <= 200000); // PRE: 1 ≤ n ≤ 2 * 10^5
        assert(c >= '0' && c <= '9'); // PRE: 0 ≤ d ≤ 9
        char s[200005];
        scanf("%s", s);
        assert(s[0] != '0'); // PRE: no leading zeros

        // Logic to insert the digit
        for (int i = 0; i < n; ++i)
        {
            if (c > s[i])
            {
                memmove(s + i + 1, s + i, n - i + 1);
                s[i] = c;
                s[n + 1] = '\0';
                printf("%s\n", s);
                assert(strlen(s) == n + 1); // POST: length of result = n + 1
                return 0;
            }
        }
        s[n] = c;
        s[n + 1] = '\0';
        printf("%s\n", s);
        assert(strlen(s) == n + 1); // POST: length of result = n + 1
    }
    return 0;
}