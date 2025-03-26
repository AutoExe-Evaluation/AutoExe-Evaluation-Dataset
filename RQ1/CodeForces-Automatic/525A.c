#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    assert(n >= 2 && n <= 100000); // PRE: n is within the range [2, 10^5]
    
    char s[2 * n];
    scanf("%s", s);
    
    int m[26] = {0};
    int ct = 0;
    
    for (int i = 0; i < 2 * n - 2; ++i)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            m[s[i] - 'a']++;
        }
        else
        {
            char c = tolower(s[i]);
            if (m[c - 'a'] > 0)
            {
                m[c - 'a']--;
            }
            else 
            {
                ct++;
            }
        }
    }
    
    printf("%d\n", ct);
    assert(ct >= 0); // POST: ct is non-negative, number of keys needed cannot be negative
    return 0;
}