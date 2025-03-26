#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

int main() {
    char s[101];
    scanf("%s", s);
    
    assert(strlen(s) >= 1 && strlen(s) <= 100); // PRE: word length is within bounds
    
    int cap = 1;
    for (int i = 1; i < strlen(s); ++i) {
        if (islower(s[i])) {
            cap = 0;
            break;
        }
    }

    if (cap) {
        for (int i = 0; i < strlen(s); ++i) {
            if (islower(s[i])) 
                s[i] = toupper(s[i]);
            else 
                s[i] = tolower(s[i]);
        }
    }
    
    printf("%s\n", s);
    assert(strcmp(s, "") != 0); // POST: output is not an empty string
    return 0;
}