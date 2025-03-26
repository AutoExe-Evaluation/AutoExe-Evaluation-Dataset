#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 4000); // PRE: 1 <= t <= 4000
    getchar(); // to skip the newline after integer input

    while (TC--)
    {
        getchar(); // to skip the empty line before each test case
        bool red = false;
        for(int i = 0; i < 8; ++i)
        {
            char s[9];
            scanf("%s", s);
            assert(strlen(s) == 8); // PRE: Each line must contain exactly 8 characters
            if(strcmp(s, "RRRRRRRR") == 0) red = true;
        }
        if(red) 
        {
            printf("R\n");
            assert(red); // POST: Red was painted last
        }
        else 
        {
            printf("B\n");
            assert(!red); // POST: Blue was painted last
        }
    }
    return 0;
}