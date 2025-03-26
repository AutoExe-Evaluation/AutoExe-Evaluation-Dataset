#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_N 200000

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 40000); // PRE: Number of test cases should be within specified limits

    for (int TC = 1; TC <= TCS; ++TC)
    {
        int n;
        char s[MAX_N + 1];
        scanf("%d %s", &n, s);
        assert(n >= 1 && n <= 200000); // PRE: Sequence length should be within specified limits
        assert(strlen(s) == n); // PRE: Length of string must match the given n

        for (int i = 0; i < strlen(s) - 1; ++i)
        {
            if (s[i] == '0' && s[i + 1] == '0')
            {
                memmove(&s[i + 1], &s[i + 2], strlen(s) - i - 1);
                i--;
            }
        }

        int ct = 0;
        for (int i = 0; i < strlen(s); ++i)
        {
            if (s[i] == '1') ct++;
        }

        assert(strlen(s) == 0 || ct > strlen(s) - ct); // POST: If ct > length of 0s, output should be YES
        if (ct > strlen(s) - ct || strlen(s) == 0) 
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}