#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    char s[200001];
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 <= t <= 10^4
    
    while (TC--) {
        scanf("%s", s);
        int last = strlen(s);
        
        // PRE: s is a positive integer without leading zeros
        for (int i = strlen(s) - 1; i >= 0; --i) {
            if (s[i] >= '5') {
                if (i - 1 < 0) {
                    memmove(s + 1, s, last);
                    s[0] = '1';
                    last = i + 1;
                } else {
                    s[i - 1]++;
                    last = i;
                }
            }
        }
        
        for (int i = last; i < strlen(s); ++i) {
            s[i] = '0';
        }
        s[last] = '\0'; // Null-terminate the string
        
        // POST: s is the maximum possible value after rounding operations
        printf("%s\n", s);
        assert(strlen(s) <= 200000); // POST: Total length of s should not exceed 2 * 10^5
    }
    return 0;
}