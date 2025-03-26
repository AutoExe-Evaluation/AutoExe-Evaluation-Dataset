#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: n is in the range [1, 100]
    
    char *s1 = " I hate that";
    char *s2 = " I love that";
    char s[500]; // Enough space for the string
    s[0] = '\0'; // Initialize empty string

    for(int i = 1; i < n; i++) {
        if(i % 2 == 1)
            strcat(s, s1);
        else
            strcat(s, s2);
    }
    
    if(n % 2 == 1) 
        strcat(s, " I hate it");
    else 
        strcat(s, " I love it");
    
    printf("%s\n", s);
    
    assert(strcmp(s + strlen(s) - 10, "I hate it") == 0 || strcmp(s + strlen(s) - 10, "I love it") == 0); // POST: The last part of the string must be "I hate it" or "I love it"
    
    return 0;
}