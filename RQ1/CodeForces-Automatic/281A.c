#include <stdio.h>
#include <ctype.h>
#include <assert.h>

int main()
{
    char s[1000];
    scanf("%s", s);
    
    assert(s[0] != '\0'); // PRE: The input word is non-empty
    
    s[0] = toupper(s[0]);
    
    assert(s[0] >= 'A' && s[0] <= 'Z'); // POST: The first letter is capitalized
    
    printf("%s\n", s);
    return 0;
}