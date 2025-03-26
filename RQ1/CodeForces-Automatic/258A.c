#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    char s[100001];
    scanf("%s", s);
    
    // PRE: The input string contains more than 1 and at most 10^5 binary digits.
    assert(strlen(s) > 1 && strlen(s) <= 100000);

    int len = strlen(s);
    
    for(int i = 0; i < len; ++i)
    {
        if(s[i] == '0')
        {
            for(int j = 0; j < i; ++j) putchar(s[j]);
            for(int j = i + 1; j < len; ++j) putchar(s[j]);
            putchar('\n');
            // POST: The output is the largest binary number possible after deleting one digit.
            assert(strlen(s) - 1 == len - 1); // Length is reduced by exactly one
            return 0;
        }
    }

    for(int i = 0; i < len - 1; ++i) putchar(s[i]);
    putchar('\n');
    
    // POST: The output is the largest binary number possible after deleting one digit.
    assert(strlen(s) - 1 == len - 1); // Length is reduced by exactly one
    return 0;
}