#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    char s[201];
    // PRE: The string s must be a non-empty string consisting only of uppercase letters and its length must not exceed 200 characters.
    scanf("%s", s);
    int len = strlen(s);
    
    assert(len > 0 && len <= 200); // Check precondition

    for (int i = 0; i < len; i++)
    {
        if (s[i] == 'W' && s[i + 1] == 'U' && s[i + 2] == 'B')
        {
            i += 2;
            if (i < len && s[i] != 'W') // Check if there are still characters left after WUB
            {
                printf(" ");
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }

    // POST: The output words should form the original song and should not contain "WUB". 
    // Each word is printed, separated by a space.
    return 0;
}