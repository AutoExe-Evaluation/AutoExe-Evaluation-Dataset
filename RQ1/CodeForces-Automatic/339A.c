#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    char s[101];
    scanf("%s", s);
    
    assert(strlen(s) > 0 && strlen(s) <= 100); // PRE: Input string is non-empty and at most 100 characters long.

    int i, j;
    int len = strlen(s);
    
    // Sort the digits in non-decreasing order
    for(i = 0; i < len; i += 2) { 
        for(j = i + 2; j < len; j += 2) {
            if(s[i] > s[j]) {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("%s\n", s);
    
    // POST: The output string should contain the same numbers in non-decreasing order.
    assert(s[0] == '1' || s[0] == '2' || s[0] == '3'); // The first character must be one of the allowed digits.
    for (i = 0; i < len - 2; i += 2) {
        assert(s[i] <= s[i + 2]); // Each value must be in non-decreasing order.
    }
    
    return 0;
}