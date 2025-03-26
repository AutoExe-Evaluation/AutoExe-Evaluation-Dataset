#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 50); // PRE: n is within the valid range [1, 50]
    
    char s[51];
    scanf("%s", s);
    
    int ct = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (s[i] == s[i + 1]) ct++;
    }
    
    printf("%d\n", ct);
    assert(ct >= 0); // POST: The count of removed stones cannot be negative
    return 0;
}