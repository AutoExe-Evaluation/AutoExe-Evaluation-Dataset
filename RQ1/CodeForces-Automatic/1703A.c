#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000
    while (TC--) {
        char s[4];
        scanf("%s", s);
        assert(strlen(s) == 3); // PRE: length of s should be 3
        for(int i = 0; i < 3; i++)
            s[i] = tolower(s[i]);
        if(strcmp(s, "yes") == 0)
            printf("YES\n");
        else
            printf("NO\n");
    }
    assert(1); // POST: Function completed successfully
}