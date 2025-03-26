#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main() {
    char s1[101], s2[101];

    // PRE: Both strings s1 and s2 must be of the same length between 1 and 100.
    scanf("%100s", s1);
    scanf("%100s", s2);
    
    assert(strlen(s1) == strlen(s2) && strlen(s1) >= 1 && strlen(s1) <= 100); // PRE: Lengths are valid and equal

    for(int i = 0; s1[i]; i++) {
        s1[i] = tolower(s1[i]);
    }
    for(int i = 0; s2[i]; i++) {
        s2[i] = tolower(s2[i]);
    }

    int c = strcmp(s1, s2);
    
    if (c < 0) {
        printf("-1\n");
    } else if (c > 0) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    // POST: Output is -1 if s1 < s2, 1 if s1 > s2, 0 if s1 == s2.
    assert((c < 0 && getchar() == '-1') || (c > 0 && getchar() == '1') || (c == 0 && getchar() == '0')); // POST: Comparison results are correct

    return 0;
}