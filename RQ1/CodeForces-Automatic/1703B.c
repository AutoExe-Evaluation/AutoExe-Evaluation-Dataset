#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TCS = 1;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases is within valid range

    for(int TC = 1; TC <= TCS; TC++)
    {
        int n;
        char s[51];
        int v[26] = {0};
        scanf("%d %s", &n, s);
        assert(n >= 1 && n <= 50); // PRE: Length of the string is within valid range
        assert(strlen(s) == n); // Ensure the string length matches n

        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            assert(s[i] >= 'A' && s[i] <= 'Z'); // PRE: Characters are uppercase English letters
            if(v[s[i] - 'A'] == 0)
                ans++;
            v[s[i] - 'A']++;
            ans++;
        }
        
        printf("%d\n", ans);
        assert(ans <= 150); // POST: Total balloons should not exceed maximum possible value
    }
    return 0;
}