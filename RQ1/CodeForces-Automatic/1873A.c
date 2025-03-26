#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 6); // PRE: 1 ≤ t ≤ 6
    
    while (TC--) {
        char s[4];
        scanf("%s", s);
        assert(strlen(s) == 3 && (s[0] == 'a' || s[0] == 'b' || s[0] == 'c') && (s[1] == 'a' || s[1] == 'b' || s[1] == 'c') && (s[2] == 'a' || s[2] == 'b' || s[2] == 'c')); // PRE: each input string is of length 3 and contains 'a', 'b', 'c' exactly once
        
        if ((s[0] == 'a' && s[1] == 'b' && s[2] == 'c') ||
            (s[0] == 'a' && s[2] == 'b' && s[1] == 'c') ||
            (s[1] == 'a' && s[0] == 'b' && s[2] == 'c') ||
            (s[1] == 'a' && s[2] == 'b' && s[0] == 'c') ||
            (s[2] == 'a' && s[0] == 'b' && s[1] == 'c') ||
            (s[2] == 'a' && s[1] == 'b' && s[0] == 'c')) {
            printf("YES\n");
            assert(1); // POST: output must contain "YES"
        } else {
            printf("NO\n");
            assert(0); // POST: output must contain "NO"
        }
    }
    return 0;
}