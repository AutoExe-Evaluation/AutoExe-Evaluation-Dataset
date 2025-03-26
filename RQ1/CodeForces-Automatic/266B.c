#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int n, t;
    
    // PRE: n and t are both within the bounds (1 ≤ n, t ≤ 50)
    scanf("%d %d", &n, &t);
    assert(n >= 1 && n <= 50); // PRE: n should be within 1 to 50
    assert(t >= 1 && t <= 50); // PRE: t should be within 1 to 50
    
    char s[51];
    scanf("%s", s);
    assert(strlen(s) == n); // PRE: Length of string s should equal n
    
    while (t--)
    {
        for (int i = 0; i < n - 1; ++i)
        {
            if (s[i] == 'B' && s[i + 1] == 'G')
            {
                char c = s[i];
                s[i] = s[i + 1];
                s[i + 1] = c;
                i++;
            }
        }
    }
    
    printf("%s\n", s);
    
    // POST: Final arrangement should be a valid string of length n consisting of 'B' and 'G'
    assert(strlen(s) == n); // POST: Length of string s should still equal n
    for (int i = 0; i < n; i++) {
        assert(s[i] == 'B' || s[i] == 'G'); // POST: Each character in string s should be either 'B' or 'G'
    }

    return 0;
}