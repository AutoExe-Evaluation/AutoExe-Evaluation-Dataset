#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    char s[51];
    scanf("%s", s);
    assert(strlen(s) > 0); // PRE: Non-empty string input

    int c4 = 0, c7 = 0;

    for (int i = 0; i < strlen(s); ++i)
    {
        if (s[i] == '4') c4++;
        else if (s[i] == '7') c7++;
    }

    if (c4 == 0 && c7 == 0) 
    {
        printf("-1\n");
        assert(1 == 0); // POST: No lucky numbers exist
    }
    else if (c4 > c7) 
    {
        printf("4\n");
        assert(c4 > 0); // POST: Lucky number 4 is present
    }
    else if (c7 > c4) 
    {
        printf("7\n");
        assert(c7 > 0); // POST: Lucky number 7 is present
    }
    else 
    {
        printf("4\n");
        assert(c4 == c7 && c4 > 0); // POST: Lucky numbers are equal
    }

    return 0;
}