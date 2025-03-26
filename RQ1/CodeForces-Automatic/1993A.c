#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXN 400

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is within bounds

    while (TCS--)
    {
        int n;
        char s[MAXN + 1];
        scanf("%d %s", &n, s);
        assert(n >= 1 && n <= 100); // PRE: n is within bounds

        int ct[4] = {0};

        for(int i = 0; s[i]; i++)
        {
            assert(s[i] == 'A' || s[i] == 'B' || s[i] == 'C' || s[i] == 'D' || s[i] == '?'); // PRE: Valid characters in answer sheet
            if(s[i] != '?') ct[s[i] - 'A']++;
        }

        int ans = 0;
        for(int i = 0; i < 4; i++)
            ans += (ct[i] < n) ? ct[i] : n;

        printf("%d\n", ans);
        assert(ans >= 0 && ans <= 4 * n); // POST: The maximum correct answers must be in range
    }
    
    return 0;
}