#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within limits

    while (TC--)
    {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(k >= 1 && k <= n && n <= 200000); // PRE: n and k are within limits

        char s[200001];
        scanf("%s", s);
        assert(strlen(s) == n); // PRE: The length of the string matches n
        
        int ct = 0;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == 'B')
            {
                ct++;
                i += k - 1;
            }
        }

        printf("%d\n", ct);
        assert(ct >= 0); // POST: Count of operations cannot be negative
    }
    return 0;
}