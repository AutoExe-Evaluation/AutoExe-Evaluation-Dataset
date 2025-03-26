#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    char s[101], t[101];
    scanf("%s", s);
    scanf("%s", t);
    
    // PRE: Lengths of s and t are both >= 1 and <= 100
    assert(strlen(s) >= 1 && strlen(s) <= 100);
    assert(strlen(t) >= 1 && strlen(t) <= 100);
    
    int len = strlen(s);
    char rs[101];
    
    for (int i = 0; i < len; i++) {
        rs[i] = s[len - 1 - i];
    }
    rs[len] = '\0';

    // POST: If t is the reverse of s, then t should equal rs
    assert(strcmp(rs, t) == 0 || strcmp(rs, t) != 0);
    
    if (strcmp(rs, t) == 0) 
        printf("YES\n");
    else 
        printf("NO\n");
    
    return 0;
}