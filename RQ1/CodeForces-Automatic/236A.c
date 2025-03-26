#include <stdio.h>
#include <assert.h>

int main()
{
    char s[101];
    int l[26] = {0};

    scanf("%s", s);
    assert(s[0] != '\0'); // PRE: input string is non-empty

    for (int i = 0; s[i] != '\0'; ++i)
    {
        l[s[i] - 'a']++;
    }
    
    int ct = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (l[i] > 0)
            ct++;
    }

    assert(ct >= 0 && ct <= 26); // POST: count of distinct characters is valid
    if (ct % 2 == 0)
        printf("CHAT WITH HER!\n");
    else
        printf("IGNORE HIM!\n");

    return 0;
}