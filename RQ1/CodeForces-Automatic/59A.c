#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main()
{
    char s[101];
    scanf("%s", s);
    
    // PRE: Length of s is between 1 and 100
    assert(strlen(s) >= 1 && strlen(s) <= 100);
    
    int lower_ct = 0, upper_ct = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (islower(s[i]))
            lower_ct++;
        else
            upper_ct++;
    }
    
    if (upper_ct > lower_ct)
    {
        for (int i = 0; s[i] != '\0'; i++)
            putchar(toupper(s[i]));
        putchar('\n');
    }
    else
    {
        for (int i = 0; s[i] != '\0'; i++)
            putchar(tolower(s[i]));
        putchar('\n');
    }
    
    // POST: The output string is either all uppercase or all lowercase
    assert((upper_ct > lower_ct && isupper(s[0])) || (lower_ct >= upper_ct && islower(s[0])));
    
    return 0;
}